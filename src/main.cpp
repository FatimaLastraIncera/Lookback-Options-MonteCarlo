#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <filesystem>

namespace fs = std::filesystem;

#include "LookbackOption.h"
#include "Greeks.h"
#include "ExactLookbackPrice.h"

/**
 * @file main.cpp
 * @brief Command-line driver: reads inputs, computes exact and Monte Carlo prices
 *        and Greeks, and writes results to files.
 */

/**
 * @brief Program entry point.
 * @return Exit code (0 = success).
 */
int main()
{
    // -------------------------------------------------------------------------
    // Define base path for input and output files
    // Files are read from and written to the executable directory
    // -------------------------------------------------------------------------
    const std::string basePath = fs::current_path().string();

    // Optional debug log
    std::ofstream log(basePath + "/debug_log.txt");
    log << "BASE PATH = " << basePath << "\n";
    log.close();

    // -------------------------------------------------------------------------
    // Read input parameters
    // -------------------------------------------------------------------------
    MCParams params;
    std::ifstream f(basePath + "/excel_inputs.txt");

    if (!f) {
        std::cerr << "ERROR: excel_inputs.txt not found in " << basePath << "\n";
        return 1;
    }

    f >> params.S0;
    f >> params.r;
    f >> params.sigma;
    f >> params.T;

    int typeInt;
    f >> typeInt;
    params.type = (typeInt == 1 ? LookbackType::Call : LookbackType::Put);

    f >> params.nPaths;
    f >> params.nSteps;

    f.close();

    // -------------------------------------------------------------------------
    // Safety defaults (avoid degenerate Monte Carlo settings)
    // -------------------------------------------------------------------------
    if (params.nSteps < 1)    params.nSteps = 50;
    if (params.nPaths < 1000) params.nPaths = 50000;

    // -------------------------------------------------------------------------
    // Exact price (closed-form)
    // -------------------------------------------------------------------------
    double exactPrice = 0.0;

    if (params.type == LookbackType::Call) {
        exactPrice = lookback_call_exact(params.S0, params.S0,
                                         params.r, params.sigma, params.T);
    } else {
        exactPrice = lookback_put_exact(params.S0, params.S0,
                                        params.r, params.sigma, params.T);
    }

    // -------------------------------------------------------------------------
    // Monte Carlo price and Greeks
    // Central finite differences with common random numbers
    // -------------------------------------------------------------------------
    const unsigned long seed = 12345UL;

    Greeks g = compute_greeks_MC(params,
                                 1.0,           // bump in S
                                 0.0001,        // bump in sigma
                                 0.01,          // bump in r
                                 1.0 / 365.0,   // bump in T
                                 seed);

    // -------------------------------------------------------------------------
    // Write numerical results (Excel-friendly)
    // -------------------------------------------------------------------------
    std::ofstream out(basePath + "/excel_results.txt");
    out << exactPrice << "\n"
        << g.price << "\n"
        << g.delta << "\n"
        << g.gamma << "\n"
        << g.theta << "\n"
        << g.rho   << "\n"
        << g.vega  << "\n";
    out.close();

    // -------------------------------------------------------------------------
    // Price curve as a function of the initial spot
    // -------------------------------------------------------------------------
    std::ofstream priceFile(basePath + "/price_curve.csv");
    priceFile << "S,Price\n";

    for (int i = 0; i <= 20; ++i) {
        const double w = static_cast<double>(i) / 20.0;
        const double S = params.S0 * (0.5 + w * (1.5 - 0.5));

        MCParams tmp = params;
        tmp.S0 = S;

        const double price = price_lookback_MC(tmp, seed);
        priceFile << S << "," << price << "\n";
    }
    priceFile.close();

    // -------------------------------------------------------------------------
    // Delta curve as a function of the initial spot
    // -------------------------------------------------------------------------
    std::ofstream deltaFile(basePath + "/delta_curve.csv");
    deltaFile << "S,Delta\n";

    for (int i = 0; i <= 20; ++i) {
        const double w = static_cast<double>(i) / 20.0;
        const double S = params.S0 * (0.5 + w * (1.5 - 0.5));

        MCParams tmp = params;
        tmp.S0 = S;

        Greeks gS = compute_greeks_MC(tmp,
                                      1.0,
                                      0.0001,
                                      0.01,
                                      1.0 / 365.0,
                                      seed);

        deltaFile << S << "," << gS.delta << "\n";
    }
    deltaFile.close();

    return 0;
}
