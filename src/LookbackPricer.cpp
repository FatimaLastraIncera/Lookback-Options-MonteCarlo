#pragma once

#include <cstddef>

// Parameters of the GBM model under the risk-neutral measure
struct GBMParams {
    double S0;     // initial price
    double r;      // risk-free rate
    double sigma;  // volatility
    double T;      // maturity
    int    steps;  // number of time steps in [0, T]
};

// Type of floating-strike lookback option
enum class LookbackType {
    FloatingCall,
    FloatingPut
};

// Result of the Monte Carlo pricing
struct MCResult {
    double price;     // estimated option price
    double stdError;  // standard error of the estimator
};

/**
 * @brief Prices a European floating-strike lookback option via Monte Carlo.
 *
 * The underlying follows a GBM under the risk-neutral measure, discretised
 * with a lognormal exact scheme. The payoff is:
 *  - Floating call:  S(T) - S_min
 *  - Floating put:   S_max - S(T)
 *
 * @param params   GBM parameters (S0, r, sigma, T, steps)
 * @param nPaths   number of Monte Carlo simulation paths
 * @param type     lookback option type (FloatingCall or FloatingPut)
 * @param seed     seed for the pseudo-random number generator
 * @return MCResult containing the price estimate and its standard error
 */
MCResult monteCarloFloatingLookbackPrice(const GBMParams& params,
                                         std::size_t nPaths,
                                         LookbackType type,
                                         unsigned long seed = 5489UL);

