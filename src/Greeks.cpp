#include "Greeks.h"
#include <cmath>

Greeks compute_greeks_MC(const MCParams& base,
                         double bumpS,
                         double bumpSigma,
                         double bumpR,
                         double bumpT,
                         unsigned long seed)
{
    Greeks g;

    // ===== PRICE =====
    g.price = price_lookback_MC(base, seed);

    // ===== DELTA =====
    MCParams up = base, dn = base;
    up.S0 = base.S0 + bumpS;
    dn.S0 = base.S0 - bumpS;

    double p_up = price_lookback_MC(up, seed);
    double p_dn = price_lookback_MC(dn, seed);

    g.delta = (p_up - p_dn) / (2.0 * bumpS);

    // ===== GAMMA =====
    g.gamma = (p_up - 2.0 * g.price + p_dn) / (bumpS * bumpS);

    // ===== VEGA =====
    MCParams sigUp = base, sigDn = base;
    sigUp.sigma = base.sigma + bumpSigma;
    sigDn.sigma = base.sigma - bumpSigma;

    double p_sigUp = price_lookback_MC(sigUp, seed);
    double p_sigDn = price_lookback_MC(sigDn, seed);

    g.vega = (p_sigUp - p_sigDn) / (2.0 * bumpSigma);

    // ===== RHO =====
    MCParams rUp = base, rDn = base;
    rUp.r = base.r + bumpR;
    rDn.r = base.r - bumpR;

    double p_rUp = price_lookback_MC(rUp, seed);
    double p_rDn = price_lookback_MC(rDn, seed);

    g.rho = (p_rUp - p_rDn) / (2.0 * bumpR);

    // ===== THETA =====
    MCParams tUp = base, tDn = base;
    tUp.T = base.T + bumpT;
    tDn.T = base.T - bumpT;

    double p_tUp = price_lookback_MC(tUp, seed);
    double p_tDn = price_lookback_MC(tDn, seed);

    g.theta = (p_tUp - p_tDn) / (2.0 * bumpT);

    return g;
}
