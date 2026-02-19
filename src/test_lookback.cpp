#include "LookbackOption.h"
#include "Greeks.h"
#include "ExactLookbackPrice.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

/**
 * @file test_lookback.cpp
 * @brief Interactive test program for the lookback option pricer.
 */

/**
 * @brief Interactive test entry point.
 * @return Exit code.
 */
int main() {
    MCParams params;
    int typeInt;

    std::cout << "===== Lookback Option Pricer (Monte Carlo) =====\n";

    std::cout << "Spot price S0: ";
    std::cin >> params.S0;

    std::cout << "Risk-free rate r: ";
    std::cin >> params.r;

    std::cout << "Volatility sigma: ";
    std::cin >> params.sigma;

    std::cout << "Time to maturity T in years: ";
    std::cin >> params.T;

    std::cout << "Option type (1 = Call, 2 = Put): ";
    std::cin >> typeInt;
    params.type = (typeInt == 1) ? LookbackType::Call : LookbackType::Put;

    std::cout << "Number of Monte Carlo paths: ";
    std::cin >> params.nPaths;

    std::cout << "Number of time-steps per path: ";
    std::cin >> params.nSteps;

    unsigned long seed = 12345UL;

    // EXACT PRICE
    double exact = 0.0;

    if (params.type == LookbackType::Call)
        exact = lookback_call_exact(params.S0, params.S0,
                                    params.r, params.sigma, params.T);
    else
        exact = lookback_put_exact(params.S0, params.S0,
                                   params.r, params.sigma, params.T);

    // MC PRICE + GREEKS 
    Greeks g = compute_greeks_MC(params, 1.0, 0.01, 0.0001, 1.0/365.0, seed);

    std::cout << "\n===== Results =====\n";
    std::cout << "Exact Price       = " << exact << "\n";
    std::cout << "MC Price          = " << g.price << "\n";
    std::cout << "Delta             = " << g.delta << "\n";
    std::cout << "Gamma             = " << g.gamma << "\n";
    std::cout << "Theta             = " << g.theta << "\n";
    std::cout << "Rho               = " << g.rho   << "\n";
    std::cout << "Vega              = " << g.vega  << "\n";
    std::cout << "Absolute Error    = " << std::fabs(g.price - exact) << "\n\n";

    return 0;
}
