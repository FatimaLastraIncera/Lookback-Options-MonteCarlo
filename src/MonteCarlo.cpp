#include "MonteCarlo.h"
#include <cmath>

MonteCarlo::MonteCarlo(double S0_, double r_, double sigma_, double T_,
                       int nSteps_, unsigned long seed)
    : S0(S0_), r(r_), sigma(sigma_), T(T_), nSteps(nSteps_),
      rng(seed), normal(0.0, 1.0)
{
}

std::vector<double> MonteCarlo::generate_path() {
    std::vector<double> path;
    path.reserve(nSteps + 1);

    double dt = T / nSteps;
    double S = S0;

    path.push_back(S);

    for (int i = 0; i < nSteps; i++) {
        double Z = normal(rng);

        // Euler discretization for GBM
        S = S * std::exp((r - 0.5 * sigma * sigma) * dt +
                         sigma * std::sqrt(dt) * Z);

        path.push_back(S);
    }

    return path;
}

