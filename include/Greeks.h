/**
 * @file Greeks.h
 * @brief Monte Carlo estimation of floating-strike lookback Greeks.
 */

#ifndef GREEKS_H
#define GREEKS_H

#include "LookbackOption.h"

/**
 * @brief Structure holding option price and sensitivities (Greeks).
 */
struct Greeks {
    double price;   ///< Option price
    double delta;   ///< Sensitivity w.r.t. underlying price
    double gamma;   ///< Second-order sensitivity w.r.t. underlying price
    double theta;   ///< Sensitivity w.r.t. time to maturity
    double vega;    ///< Sensitivity w.r.t. volatility
    double rho;     ///< Sensitivity w.r.t. interest rate
};

/**
 * @brief Compute option price and Greeks using Monte Carlo finite differences.
 *
 * @param base Base Monte Carlo parameters.
 * @param bumpS Bump size for underlying price (for Gamma calculation).
 * @param bumpSigma Bump size for volatility (unused pathwise here).
 * @param bumpR Bump size for interest rate (for Rho calculation).
 * @param bumpT Bump size for maturity (for Theta calculation).
 * @param seed RNG seed for reproducible runs.
 * @return Greeks structure containing price and sensitivities.
 */
Greeks compute_greeks_MC(const MCParams& base,
                         double bumpS,      // bump for underlying price
                         double bumpSigma, // bump for volatility
                         double bumpR,     // bump for interest rate
                         double bumpT,     // bump for maturity
                         unsigned long seed);

#endif // GREEKS_H