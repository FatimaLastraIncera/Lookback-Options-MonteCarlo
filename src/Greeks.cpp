// -----------------------------------------------------------------------------
// Greeks.cpp
// Monte Carlo estimation of floating-strike lookback Greeks (PLAIN MC)
// - Delta & Vega: Pathwise 
// - Gamma, Rho, Theta: Finite differences (CRN via same seed)
// -----------------------------------------------------------------------------

#include "Greeks.h"
#include <cmath>
#include <random>
#include <algorithm>
#include <vector>

/**
 * @brief Forward declaration of Monte Carlo pricer used in Greeks computations.
 */
double price_lookback_MC(const MCParams& p, unsigned long seed);

/**
 * @brief Compute price, delta and vega pathwise in a single Monte Carlo run.
 *
 * This uses a pathwise derivative approach for Delta and Vega while
 * accumulating the discounted payoff for price.
 *
 * @param p Monte Carlo parameters.
 * @param seed RNG seed for reproducibility.
 * @param outPrice Output parameter for price.
 * @param outDelta Output parameter for delta.
 * @param outVega Output parameter for vega.
 */
static void price_delta_vega_pathwise(const MCParams& p,
                                      unsigned long seed,
                                      double& outPrice,
                                      double& outDelta,
                                      double& outVega)
{
    const int    N  = std::max(1, p.nSteps);
    const double T  = p.T;
    const double dt = T / static_cast<double>(N);
    const double sqrtdt = std::sqrt(dt);
    const double disc = std::exp(-p.r * T);

    std::mt19937_64 rng(seed);
    std::normal_distribution<double> nd(0.0, 1.0);

    double sumPayoff = 0.0;
    double sumDelta  = 0.0;
    double sumVega   = 0.0;

    for (int i = 0; i < p.nPaths; ++i) {

        double S = p.S0;

        double Smin = S;
        double Smax = S;

        double D = 0.0;        // dS/dsigma
        double D_at_min = 0.0;
        double D_at_max = 0.0;

        for (int k = 0; k < N; ++k) {
            const double Z = nd(rng);

            const double step =
                std::exp((p.r - 0.5 * p.sigma * p.sigma) * dt + p.sigma * sqrtdt * Z);

            const double S_next = S * step;

            const double D_next =
                S_next * ( (S != 0.0 ? (D / S) : 0.0) + (-p.sigma * dt + sqrtdt * Z) );

            S = S_next;
            D = D_next;

            if (S < Smin) { Smin = S; D_at_min = D; }
            if (S > Smax) { Smax = S; D_at_max = D; }
        }

        const double ST = S;
        const double DT = D;

        double payoff = 0.0;
        double dPayoff_dSigma = 0.0;

        if (p.type == LookbackType::Call) {
            payoff = ST - Smin;
            dPayoff_dSigma = DT - D_at_min;
        } else {
            payoff = Smax - ST;
            dPayoff_dSigma = D_at_max - DT;
        }

        const double dPayoff_dS0 = (p.S0 != 0.0) ? (payoff / p.S0) : 0.0;

        sumPayoff += payoff;
        sumDelta  += dPayoff_dS0;
        sumVega   += dPayoff_dSigma;
    }

    const double invM = 1.0 / static_cast<double>(p.nPaths);

    outPrice = disc * (sumPayoff * invM);
    outDelta = disc * (sumDelta  * invM);
    outVega  = disc * (sumVega   * invM);
}

/**
 * @brief Compute option price and Greeks using Monte Carlo.
 *
 * Delta and Vega are computed pathwise; Gamma, Rho and Theta use central
 * finite differences with common random numbers for variance reduction.
 *
 * @param base Base Monte Carlo parameters.
 * @param bumpS Bump for underlying price (Gamma calculation).
 * @param bumpR Bump for interest rate (Rho calculation).
 * @param bumpT Bump for maturity (Theta calculation).
 * @param seed RNG seed for reproducibility.
 * @return Greeks structure with computed sensitivities.
 */
Greeks compute_greeks_MC(const MCParams& base,
                         double bumpS,
                         double bumpSigma,
                         double bumpR,
                         double bumpT,
                         unsigned long seed)
{
    Greeks g{};

    // PRICE + PATHWISE DELTA & VEGA (single MC run)
    price_delta_vega_pathwise(base, seed, g.price, g.delta, g.vega);

    // GAMMA (FD in S0) with CRN
    MCParams up = base, dn = base;
    up.S0 = base.S0 + bumpS;
    dn.S0 = base.S0 - bumpS;

    const double p_up = price_lookback_MC(up, seed);
    const double p_dn = price_lookback_MC(dn, seed);
    const double p_0 = price_lookback_MC(base, seed);

    g.gamma = (p_up - 2.0 * p_0 + p_dn) / (bumpS * bumpS);

    // RHO (FD in r) with CRN
    MCParams rUp = base, rDn = base;
    rUp.r = base.r + bumpR;
    rDn.r = base.r - bumpR;

    const double p_rUp = price_lookback_MC(rUp, seed);
    const double p_rDn = price_lookback_MC(rDn, seed);

    g.rho = (p_rUp - p_rDn) / (2.0 * bumpR);

    // THETA (FD in T) with CRN
    MCParams tUp = base, tDn = base;
    tUp.T = base.T + bumpT;
    tDn.T = base.T - bumpT;

    const double p_tUp = price_lookback_MC(tUp, seed);
    const double p_tDn = price_lookback_MC(tDn, seed);

    g.theta = -(p_tUp - p_tDn) / (2.0 * bumpT);

    return g;
}
