#include "LookbackOption.h"
#include "MonteCarlo.h"
#include <algorithm>
#include <cmath>

double payoff_lookback(double ST, double Smin, double Smax, LookbackType type) {
    if (type == LookbackType::Call) 
        return std::max(ST - Smin, 0.0);
    else 
        return std::max(Smax - ST, 0.0);
}

double price_lookback_MC(const MCParams& params, unsigned long seed) {
    MonteCarlo mc(params.S0, params.r, params.sigma, params.T,
                  params.nSteps, seed);

    double sumPayoff = 0.0;

    for (int p = 0; p < params.nPaths; p++) {
        std::vector<double> path = mc.generate_path();

        double ST   = path.back();
        double Smin = *std::min_element(path.begin(), path.end());
        double Smax = *std::max_element(path.begin(), path.end());

        sumPayoff += payoff_lookback(ST, Smin, Smax, params.type);
    }

    return std::exp(-params.r * params.T) * (sumPayoff / params.nPaths);
}

