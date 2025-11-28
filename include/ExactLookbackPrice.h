#ifndef EXACTPRICE_H
#define EXACTPRICE_H

double lookback_call_exact(double S0, double Smin,
                           double r, double sigma, double T);

double lookback_put_exact(double S0, double Smax,
                          double r, double sigma, double T);

#endif 
