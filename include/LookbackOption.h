/**
 * @file LookbackOption.h
 * @brief Data structures and functions for pricing floating-strike lookback
 *        options using Monte Carlo simulation.
 */

#ifndef LOOKBACK_OPTION_H
#define LOOKBACK_OPTION_H

#include <vector>
#include <string>

/**
 * @brief Type of lookback option.
 */
enum class LookbackType {
    Call,
    Put
};

/**
 * @brief Parameters for Monte Carlo pricing.
 */
struct MCParams {
    double S0;
    double r;
    double sigma;
    double T;
    LookbackType type;
    int nPaths;
    int nSteps;
};

/**
 * @brief Payoff of a floating-strike lookback option.
 *
 * @param ST Terminal spot price.
 * @param minS Minimum spot along the path.
 * @param maxS Maximum spot along the path.
 * @param type Option type (Call/Put).
 * @return Payoff value for the path.
 */
double payoff_lookback(double ST, double minS, double maxS, LookbackType type);

/**
 * @brief Monte Carlo pricing of a floating-strike lookback option.
 *
 * @param params Monte Carlo parameters (see `MCParams`).
 * @param seed RNG seed (default = 123).
 * @return Discounted Monte Carlo price.
 */
double price_lookback_MC(const MCParams& params, unsigned long seed = 123);

#endif // LOOKBACK_OPTION_H

