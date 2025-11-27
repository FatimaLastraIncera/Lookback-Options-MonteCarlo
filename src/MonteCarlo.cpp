#include "LookbackPricer.h"

#include <random>
#include <cmath>

MCResult monteCarloFloatingLookbackPrice(const GBMParams& params,
                                         std::size_t nPaths,
                                         LookbackType type,
                                         unsigned long seed)
{
    const double S0    = params.S0;
    const double r     = params.r;
    const double sigma = params.sigma;
    const double T     = params.T;
    const int    steps = params.steps;

    const double dt    = T / static_cast<double>(steps);
    const double drift = (r - 0.5 * sigma * sigma) * dt;
    const double volDt = sigma * std::sqrt(dt);
    const double disc  = std::exp(-r * T);

    // Random number generator
    std::mt19937_64 rng(seed);
    std::normal_distribution<double> norm(0.0, 1.0);

    double sumPayoff   = 0.0;
    double sumPayoffSq = 0.0;

    for (std::size_t path = 0; path < nPaths; ++path) {
        double S = S0;
        double S_min = S0;
        double S_max = S0;

        // Simulate one GBM path
        for (int i = 0; i < steps; ++i) {
            double Z = norm(rng);
            S *= std::exp(drift + volDt * Z);

            if (S < S_min) S_min = S;
            if (S > S_max) S_max = S;
        }

        // Compute payoff at maturity
        double payoff = 0.0;
        if (type == LookbackType::FloatingCall) {
            payoff = S - S_min;      // S(T) - S_min
        } else { // FloatingPut
            payoff = S_max - S;      // S_max - S(T)
        }

        if (payoff < 0.0) {
            payoff = 0.0; // Just in case of numerical issues
        }

        double discounted = disc * payoff;
        sumPayoff   += discounted;
        sumPayoffSq += discounted * discounted;
    }

    MCResult result{};
    if (nPaths > 1) {
        double n = static_cast<double>(nPaths);
        double mean = sumPayoff / n;
        double meanSq = sumPayoffSq / n;
        double variance = meanSq - mean * mean;
        if (variance < 0.0) variance = 0.0; // numerical safety

        result.price    = mean;
        result.stdError = std::sqrt(variance / (n - 1.0));
    } else {
        result.price    = sumPayoff;
        result.stdError = 0.0;
    }

    return result;
}

