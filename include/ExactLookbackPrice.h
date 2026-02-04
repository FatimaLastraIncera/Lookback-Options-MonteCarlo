/**
 * @file ExactLookbackPrice.h
 * @brief Exact closed-form pricing formulas for floating-strike lookback options.
 */
#ifndef EXACTPRICE_H
#define EXACTPRICE_H

/**
 * @brief Exact price of a floating-strike lookback CALL option (Goldman, 1979).
 *
 * @param S0 Current spot price.
 * @param Smin Minimum observed spot along the path.
 * @param r Risk-free rate.
 * @param sigma Volatility.
 * @param T Time to maturity.
 * @return Exact call price.
 */
double lookback_call_exact(double S0,
                           double Smin,
                           double r,
                           double sigma,
                           double T);

/**
 * @brief Exact price of a floating-strike lookback PUT option (Goldman, 1979).
 *
 * @param S0 Current spot price.
 * @param Smax Maximum observed spot along the path.
 * @param r Risk-free rate.
 * @param sigma Volatility.
 * @param T Time to maturity.
 * @return Exact put price.
 */
double lookback_put_exact(double S0,
                          double Smax,
                          double r,
                          double sigma,
                          double T);

#endif // EXACTLOOKBACKPRICE_H