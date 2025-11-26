# Lookback Option Pricing Library 

## Overview

The **Lookback Option Pricing Library** is a C++ project designed to price **European lookback options** using Monte Carlo simulation under the Black–Scholes model. The library computes both the option price and the full set of Greeks (Delta, Gamma, Theta, Rho, Vega), and includes an Excel-based interface for user interaction.


Lookback options are path-dependent derivatives whose payoff depends on the maximum or minimum value reached by the underlying asset over the entire life of the contract. Because the payoff depends on the full price trajectory rather than only the terminal value, closed-form analytical pricing formulas are generally not available under the Black--Scholes framework. Numerical methods are therefore required to obtain accurate valuations. This project implements a complete C++ Monte Carlo engine to price European Lookback options under Geometric Brownian Motion. In addition to option pricing, the library computes the full set of Greeks (Delta, Gamma, Theta, Vega, and Rho) using finite-difference estimators. The C++ numerical core is compiled into a dynamic library (DLL) and connected to an Excel interface through VBA, allowing users to input parameters, run simulations, and visualise outputs interactively.
The resulting tool provides an efficient and modular pricing framework that integrates numerical methods, software engineering practices, and a user-friendly interface. It illustrates how Monte Carlo techniques can be used to value complex path-dependent options for which no closed-form solutions exist.
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

