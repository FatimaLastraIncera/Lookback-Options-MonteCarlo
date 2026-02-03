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

### • Greeks are computed within the Monte Carlo framework using: finite--difference estimators for Gamma, Theta and Rho and pathwise estimators for Delta and Vega
<img width="687" height="362" alt="image" src="https://github.com/user-attachments/assets/11042f22-825e-4f32-9736-70bc71bbd3c3" />


## References

1. **Andersen, L.** (1996). *Exact exotics*. **Risk**.  

2. **Black, F. and Scholes, M.** (1973). *The pricing of options and corporate liabilities*.  
   **Journal of Political Economy**, 81(3), 637–654.  

3. **Glasserman, P.** (2003). *Monte Carlo Methods in Financial Engineering*.  
   **Stochastic Modelling and Applied Probability**, Springer, New York.  

4. **Goldman, M. B., Sosin, H. B., and Gatto, M. A.** (1979).  
   *Path dependent options: “buy at the low, sell at the high”*.  
   **Journal of Finance**, 34(5), 1111–1127.  
---

## License

MIT License.

