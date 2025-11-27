#include <iostream>
#include <iomanip>
#include "LookbackPricer.hpp"

int main() {
    // Example parameters
    GBMParams params;
    params.S0    = 100.0;
    params.r     = 0.05;
    params.sigma = 0.20;
    params.T     = 1.0;     // 1 year
    params.steps = 252;     // daily steps (approx.)

    std::size_t nPaths = 100000; // Monte Carlo paths
    unsigned long seed = 12345UL;

    // Price floating-strike lookback call
    MCResult callRes = monteCarloFloatingLookbackPrice(
        params,
        nPaths,
        LookbackType::FloatingCall,
        seed
    );

    // Price floating-strike lookback put
    MCResult putRes = monteCarloFloatingLookbackPrice(
        params,
        nPaths,
        LookbackType::FloatingPut,
        seed + 1 // different seed for independence (optional)
    );

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "Floating-strike lookback call price: "
              << callRes.price
              << " (std. error = " << callRes.stdError << ")\n";

    std::cout << "Floating-strike lookback put price:  "
              << putRes.price
              << " (std. error = " << putRes.stdError << ")\n";

    return 0;
}

