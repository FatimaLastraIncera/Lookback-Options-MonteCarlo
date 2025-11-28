#ifndef GREEKS_H
#define GREEKS_H

#include "LookbackOption.h"

struct Greeks {
    double price;
    double delta;
    double gamma;
    double theta;
    double vega;
    double rho;
};


Greeks compute_greeks_MC(const MCParams& base,
                         double bumpS,
                         double bumpSigma,
                         double bumpR,
                         double bumpT,
                         unsigned long seed);

#endif
