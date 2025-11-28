// MonteCarlo.h
#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <vector>
#include <random>

class MonteCarlo {
public:
    MonteCarlo(double S0, double r, double sigma, double T,
               int nSteps, unsigned long seed);

    std::vector<double> generate_path();

private:
    double S0, r, sigma, T;
    int nSteps;

    std::mt19937 rng;
    std::normal_distribution<double> normal;
};

#endif

