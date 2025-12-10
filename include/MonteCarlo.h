// -----------------------------------------------------------------------------
// MonteCarlo.h
// Definition of a Monte Carlo engine for simulating price paths
// under a Geometric Brownian Motion model
// -----------------------------------------------------------------------------

#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <vector>
#include <random>

class MonteCarlo {
public:
    // Constructor: initializes model parameters and random number generator
    MonteCarlo(double S0,
               double r,
               double sigma,
               double T,
               int nSteps,
               unsigned long seed);

    std::vector<double> generate_path();

private:
    // Model parameters
    double S0;      // initial asset price
    double r;       // risk-free interest rate
    double sigma;   // volatility
    double T;       // time to maturity
    int nSteps;     // number of time steps

    // Random number generation
    std::mt19937 rng;                          // Mersenne Twister RNG
    std::normal_distribution<double> normal;   // standard normal distribution
};

#endif // MONTECARLO_H

