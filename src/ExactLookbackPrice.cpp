#include "ExactLookbackPrice.h"
#include <cmath>

// Normal CDF (approximation – good enough for pricing)
double norm_cdf(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2.0));
}

// -------- Floating-strike Lookback Call (Goldman 1979) --------
double lookback_call_exact(double S0, double Smin,
                           double r, double sigma, double T)
{
    double sqrtT = std::sqrt(T);
    double sig2 = sigma * sigma;

    double a1 = ( std::log(S0 / Smin) + (r + 0.5 * sig2) * T ) / (sigma * sqrtT);
    double a2 = a1 - sigma * sqrtT;
    double a3 = ( std::log(S0 / Smin) + (-r + 0.5 * sig2) * T ) / (sigma * sqrtT);

    double Y1 = -2.0 * (r - 0.5 * sig2) * std::log(S0 / Smin) / sig2;

    double part1 = S0 * ( norm_cdf(a1) - (sig2/(2*r)) * norm_cdf(-a1) );
    double part2 = -Smin * std::exp(-r*T)
                   * ( norm_cdf(a2) - (sig2/(2*r)) * std::exp(Y1) * norm_cdf(-a3) );

    return part1 + part2;
}

// -------- Floating-strike Lookback Put (Goldman 1979) --------
double lookback_put_exact(double S0, double Smax,
                          double r, double sigma, double T)
{
    double sqrtT = std::sqrt(T);
    double sig2 = sigma * sigma;

    double b1 = ( std::log(Smax / S0) + (-r + 0.5 * sig2) * T ) / (sigma * sqrtT);
    double b2 = b1 - sigma * sqrtT;
    double b3 = ( std::log(Smax / S0) + (r - 0.5 * sig2) * T ) / (sigma * sqrtT);

    double Y2 = 2.0 * (r - 0.5 * sig2) * std::log(S0 / Smax) / sig2;

    double part1 = Smax * std::exp(-r*T)
                   * ( norm_cdf(b1) - (sig2/(2*r)) * std::exp(Y2) * norm_cdf(-b3) );

    double part2 =  S0 * ( (sig2/(2*r)) * norm_cdf(-b2) - norm_cdf(b2) );

    return part1 + part2;
}
