// -----------------------------------------------------------------------------
// Greeks.h
// Monte Carlo estimation of floating-strike lookback Greeks 
// -----------------------------------------------------------------------------

#ifndef GREEKS_H
#define GREEKS_H

#include "LookbackOption.h"

// -----------------------------------------------------------------------------
// Structure holding option price and sensitivities (Greeks)
// -----------------------------------------------------------------------------
struct Greeks {
    double price;   // option price
    double delta;   // sensitivity w.r.t. underlying price
    double gamma;   // second-order sensitivity w.r.t. underlying price
    double theta;   // sensitivity w.r.t. time to maturity
    double vega;    // sensitivity w.r.t. volatility
    double rho;     // sensitivity w.r.t. interest rate
};

// -----------------------------------------------------------------------------
// Compute option price and Greeks using Monte Carlo finite differences
// -----------------------------------------------------------------------------
Greeks compute_greeks_MC(const MCParams& base,
                         double bumpS,      // bump for underlying price
                         double bumpSigma, // bump for volatility
                         double bumpR,     // bump for interest rate
                         double bumpT,     // bump for maturity
                         unsigned long seed);

#endif // GREEKS_H