#include "ExactLookbackPrice.h"
#include <cmath>

/**
 * @brief Standard normal cumulative distribution function using `erfc`.
 * @param x Input value.
 * @return CDF of standard normal at `x`.
 */
double norm_cdf(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2.0));
}

/**
 * @brief Exact price of a floating-strike lookback Call (Goldman, 1979).
 *
 * @param S0 Current spot price.
 * @param Smin Minimum observed spot.
 * @param r Risk-free rate.
 * @param sigma Volatility.
 * @param T Time to maturity.
 * @return Exact call price.
 */
double lookback_call_exact(const double S0,
                           const double Smin,
                           const double r,
                           const double sigma,
                           const double T)
{
    // Precompute frequently used quantities
    const double sqrtT = std::sqrt(T);
    const double sig2  = sigma * sigma;
    const double logSM = std::log(S0 / Smin);

    // Auxiliary variables from the closed-form formula
    const double a1 = (logSM + (r + 0.5 * sig2) * T) / (sigma * sqrtT);
    const double a2 = a1 - sigma * sqrtT;
    const double a3 = (logSM + (-r + 0.5 * sig2) * T) / (sigma * sqrtT);

    // Drift adjustment term
    const double Y1 = -2.0 * (r - 0.5 * sig2) * logSM / sig2;

    // Discount factor and volatility coefficient
    const double discount = std::exp(-r * T);
    const double coeff    = sig2 / (2.0 * r);

    // Pricing formula
    const double part1 = S0 * ( norm_cdf(a1) - coeff * norm_cdf(-a1) );
    const double part2 = -Smin * discount * ( norm_cdf(a2) - coeff * std::exp(Y1) * norm_cdf(-a3) );

    return part1 + part2;
}

/**
 * @brief Exact price of a floating-strike lookback Put (Goldman, 1979).
 *
 * @param S0 Current spot price.
 * @param Smax Maximum observed spot.
 * @param r Risk-free rate.
 * @param sigma Volatility.
 * @param T Time to maturity.
 * @return Exact put price.
 */
double lookback_put_exact(const double S0, 
                          const double Smax,
                          const double r,
                          const double sigma,
                          const double T)
{
    // Precompute frequently used quantities
    const double sqrtT = std::sqrt(T);
    const double sig2  = sigma * sigma;
    const double logMS = std::log(Smax / S0);

    // Auxiliary variables from the closed-form formula
    const double b1 = (logMS + (-r + 0.5 * sig2) * T) / (sigma * sqrtT);
    const double b2 = b1 - sigma * sqrtT;
    const double b3 = (logMS + (r - 0.5 * sig2) * T) / (sigma * sqrtT);

    // Drift adjustment term from the reflection principle
    const double Y2 = 2.0 * (r - 0.5 * sig2) * std::log(S0 / Smax) / sig2;

    // Discount factor and volatility coefficient
    const double discount = std::exp(-r * T);
    const double coeff = sig2 / (2.0 * r);

    // Pricing formula
    const double part1 = Smax * discount * ( norm_cdf(b1) - coeff * std::exp(Y2) * norm_cdf(-b3) );
    const double part2 = S0 * ( coeff * norm_cdf(-b2) - norm_cdf(b2) );

    return part1 + part2;
}