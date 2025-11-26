# Lookback Option Pricing Library 

## Overview

The **Lookback Option Pricing Library** is a C++ project designed to price **European lookback options** using Monte Carlo simulation under the Black–Scholes model. The library computes both the option price and the full set of Greeks (Delta, Gamma, Theta, Rho, Vega), and includes an Excel-based interface for user interaction.

---

## Features

### • Lookback Option Representation  
Support for European lookback **calls** and **puts**, parameterized by:  
- Spot price \(S_0\)  
- Risk-free rate \(r\)  
- Volatility \(\sigma\)  
- Maturity \(T\)  
- Number of Monte Carlo paths  
- Time discretization steps  

### • Monte Carlo Pricing (Black–Scholes framework)
- Simulation of geometric Brownian motion paths.  
- Tracking of the **running minimum** (call) or **running maximum** (put).  
- Discounted expected payoff estimator.  
- Variance reduction techniques (optional extension).

### • Greeks calculation: computed numerically using finite-difference estimators (Delta, Gamma, Theta, Rho, Vega).
---

*Insert here a screenshot of your Excel interface with inputs, results, and graphs.*

---

## References

1. **John Hull**, *Options, Futures and Other Derivatives*, Pearson (2011).  
2. **Paul Glasserman**, *Monte Carlo Methods in Financial Engineering*, Springer (2003).  
3. **Emmanuel Gobet**, *Monte Carlo Methods and Stochastic Processes*, CRC Press (2016).  
4. **Paul Wilmott**, *Mathematics of Financial Derivatives*, Wiley (1995).

---

## License

MIT License.

