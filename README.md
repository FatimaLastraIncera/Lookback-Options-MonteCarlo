# Lookback Option Pricing Library (Monte Carlo – C++)

## Overview

The **Lookback Option Pricing Library** is a C++ project designed to price **European lookback options** using Monte Carlo simulation under the Black–Scholes model.  
The library computes both the option price and the full set of Greeks (Delta, Gamma, Theta, Rho, Vega), and includes an Excel-based interface for user interaction.

This project was developed as part of the **M2 Ingénierie et Finance** program.

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

### • Greeks Calculation  
Computed numerically using finite-difference estimators:
- **Delta:** \(\partial P / \partial S\)  
- **Gamma:** \(\partial^2 P / \partial S^2\)  
- **Theta:** \(\partial P / \partial t\)  
- **Rho:** \(\partial P / \partial r\)  
- **Vega:** \(\partial P / \partial \sigma\)

### • Excel Interface  
An Excel file (VBA or XLL) is provided to:  
- Input all option parameters  
- Trigger the C++ pricer  
- Display the price and Greeks  
- Generate graphs for:  
  - Price \(P(S, T_0)\) vs. spot  
  - Delta \(\Delta(S, T_0)\) vs. spot  

---

## Model Description

The payoff of a **European lookback call** is:
\[
P_{\text{call}} = S(T) - \min_{T_0 \le t \le T} S(t)
\]

The payoff of a **European lookback put** is:
\[
P_{\text{put}} = \max_{T_0 \le t \le T} S(t) - S(T)
\]

Under Black–Scholes dynamics:
\[
S_{t+\Delta t} = S_t \exp\left((r - \tfrac{1}{2}\sigma^2)\Delta t + 
\sigma\sqrt{\Delta t}\,Z\right)
\]

Monte Carlo simulation is used to approximate the expectation under the risk-neutral measure.

---

## Outputs

The C++ code computes the following:

| Quantity | Description |
|---------|-------------|
| Price | Theoretical Monte Carlo price |
| Delta | Sensitivity to spot price |
| Gamma | Sensitivity to second-order changes in spot |
| Theta | Sensitivity to time |
| Vega | Sensitivity to volatility |
| Rho | Sensitivity to interest rate |
| Price graph | \(P(S,T_0)\) as a function of spot |
| Delta graph | \(\Delta(S,T_0)\) as a function of spot |

---

## Example (Excel Interface Preview)

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

