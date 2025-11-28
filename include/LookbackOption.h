#ifndef LOOKBACK_OPTION_H
#define LOOKBACK_OPTION_H

#include <vector>
#include <string>

enum class LookbackType { Call, Put };

struct MCParams {
    double S0;
    double r;
    double sigma;
    double T;
    LookbackType type;
    int nPaths;
    int nSteps;
};

/// Payoff of a floating-strike lookback option
double payoff_lookback(double ST, double minS, double maxS, LookbackType type);

/// Monte Carlo pricing of lookback option
double price_lookback_MC(const MCParams& params, unsigned long seed = 123);

#endif

