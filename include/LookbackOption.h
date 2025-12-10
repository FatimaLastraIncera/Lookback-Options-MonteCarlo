// -----------------------------------------------------------------------------
// LookbackOption.h
// Definition of data structures and functions for pricing floating-strike lookback 
// options using Monte Carlo simulation
// -----------------------------------------------------------------------------

#ifndef LOOKBACK_OPTION_H
#define LOOKBACK_OPTION_H

#include <vector>
#include <string>

// -----------------------------------------------------------------------------
// Type of lookback option
// -----------------------------------------------------------------------------
enum class LookbackType {
    Call,
    Put
};

// -----------------------------------------------------------------------------
// Parameters for Monte Carlo pricing
// -----------------------------------------------------------------------------
struct MCParams {
    double S0;
    double r;
    double sigma;
    double T;
    LookbackType type;
    int nPaths;
    int nSteps;
};

// -----------------------------------------------------------------------------
// Payoff of a floating-strike lookback option
// -----------------------------------------------------------------------------
double payoff_lookback(double ST, double minS, double maxS, LookbackType type);

// -----------------------------------------------------------------------------
// Monte Carlo pricing of a floating-strike lookback option
// -----------------------------------------------------------------------------
double price_lookback_MC(const MCParams& params, unsigned long seed = 123);

#endif // LOOKBACK_OPTION_H

