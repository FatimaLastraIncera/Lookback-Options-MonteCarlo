#pragma once

#include <cstddef>
#include "LookbackPricer.h"

MCResult monteCarloFloatingLookbackPrice(const GBMParams& params,
                                         std::size_t nPaths,
                                         LookbackType type,
                                         unsigned long seed = 5489UL);
