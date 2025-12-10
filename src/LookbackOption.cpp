#include "LookbackOption.h"
#include "MonteCarlo.h"
#include <algorithm>
#include <cmath>
#include <vector>

// -----------------------------------------------------------------------------
// Payoff of a floating-strike lookback option
// -----------------------------------------------------------------------------
double payoff_lookback(const double ST,
                       const double Smin,
                       const double Smax,
                       const LookbackType type)
{
    if (type == LookbackType::Call)
        return std::max(ST - Smin, 0.0);
    else
        return std::max(Smax - ST, 0.0);
}

// -----------------------------------------------------------------------------
// Monte Carlo pricing of a floating-strike lookback option
// -----------------------------------------------------------------------------
double price_lookback_MC(const MCParams& params,
                         const unsigned long seed)
{
    MonteCarlo mc(params.S0,
                  params.r,
                  params.sigma,
                  params.T,
                  params.nSteps,
                  seed);

    double sumPayoff = 0.0;

    for (int p = 0; p < params.nPaths; ++p)
    {
        const std::vector<double> path = mc.generate_path();

        // Extract terminal price and path extremes
        const double ST   = path.back();
        const double Smin = *std::min_element(path.begin(), path.end());
        const double Smax = *std::max_element(path.begin(), path.end());

        // Compute and accumulate payoff for the given path
        sumPayoff += payoff_lookback(ST, Smin, Smax, params.type);
    }

    // Discount the average payoff to present value
    const double discountedPayoff =
        std::exp(-params.r * params.T) * (sumPayoff / params.nPaths);

    return discountedPayoff;
}

