/**
 * @file MonteCarlo.h
 * @brief Monte Carlo engine for simulating price paths under
 *        a Geometric Brownian Motion model.
 */

#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <vector>
#include <random>

class MonteCarlo {
public:
    /**
     * @brief Construct a Monte Carlo engine.
     *
     * @param S0 Initial asset price.
     * @param r Risk-free rate.
     * @param sigma Volatility.
     * @param T Time to maturity.
     * @param nSteps Number of time steps per path.
     * @param seed RNG seed.
     */
    MonteCarlo(double S0,
               double r,
               double sigma,
               double T,
               int nSteps,
               unsigned long seed);

    /**
     * @brief Generate a single simulated price path.
     * @return Vector of spot prices (size = nSteps + 1).
     */
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

