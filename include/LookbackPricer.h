#pragma once

#include <cstddef>

// ---------------------------
//   GBM PARAMETERS
// ---------------------------
struct GBMParams {
    double S0;
    double r;
    double sigma;
    double T;
    int steps;
};

// ---------------------------
//   LOOKBACK TYPES
// ---------------------------
enum class LookbackType {
    FloatingCall,
    FloatingPut
};

// ---------------------------
//   MONTE CARLO RESULT
// ---------------------------
struct MCResult {
    double price;
    double stdError;
};

// ---------------------------
//   PRICER PROTOTYPE
// ---------------------------
MCResult monteCarloFloatingLookbackPrice(const GBMParams& params,
                                         std::size_t nPaths,
                                         LookbackType type,
                                         unsigned long seed = 5489UL);
