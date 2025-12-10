// -----------------------------------------------------------------------------
// ExactLookbackPrice.h
// Exact closed-form pricing formulas for floating-strike lookback options
// -----------------------------------------------------------------------------
#ifndef EXACTPRICE_H
#define EXACTPRICE_H

// -----------------------------------------------------------------------------
// Exact price of a floating-strike lookback CALL option (Goldman, 1979)
// -----------------------------------------------------------------------------
double lookback_call_exact(double S0,
                           double Smin,
                           double r,
                           double sigma,
                           double T);

// -----------------------------------------------------------------------------
// Exact price of a floating-strike lookback PUT option (Goldman, 1979)
// -----------------------------------------------------------------------------
double lookback_put_exact(double S0,
                          double Smax,
                          double r,
                          double sigma,
                          double T);

#endif // EXACTLOOKBACKPRICE_H