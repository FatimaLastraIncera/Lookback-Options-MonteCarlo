#include "MonteCarlo.h"
#include <cmath>
#include <vector>

// -----------------------------------------------------------------------------
// Constructor: initializes model parameters and random number generator
// -----------------------------------------------------------------------------
MonteCarlo::MonteCarlo(const double S0_,
                       const double r_,
                       const double sigma_,
                       const double T_,
                       const int nSteps_,
                       const unsigned long seed)
    : S0(S0_),
      r(r_),
      sigma(sigma_),
      T(T_),
      nSteps(nSteps_),
      rng(seed),
      normal(0.0, 1.0)
{
}

// -----------------------------------------------------------------------------
// Generate one price path using Euler discretization of a Geometric Brownian Motion
// -----------------------------------------------------------------------------
std::vector<double> MonteCarlo::generate_path()
{
    // Time step
    const double dt = T / nSteps;

    // Precompute constants
    const double drift = (r - 0.5 * sigma * sigma) * dt;
    const double diffusion = sigma * std::sqrt(dt);

    // Container for the simulated path
    std::vector<double> path;
    path.reserve(nSteps + 1);

    double S = S0;
    path.push_back(S);

    // Simulate the path
    for (int i = 0; i < nSteps; ++i)
    {
        const double Z = normal(rng);  // standard normal increment

        // Euler–Maruyama scheme for Geometric Brownian Motion
        S *= std::exp(drift + diffusion * Z);

        path.push_back(S);
    }

    return path;
}
