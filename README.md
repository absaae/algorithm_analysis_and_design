## Practice 3 - Binary Search

Analysis of iterative and recursive binary search, focusing on theretical complexity derivation
and experimental validation.

### Implementations

1. **Iterative**: Uses a while loop with two pointers narrowing the search range each step.
2. **Recursive**: Divides the array in half at each call; analyzed via recurrence relation and Master Theorem.


### Complexity

Both implementations yield **0(logn)**, consistent with the Invariance principle. 
- Iterative: `T(n) = 14[log(n)] + 8`
- Recursive: `T(n) = 20*log(n) + 7`, derived from `T(n) = T(n/2) + 20`

Validated with the Master Theorem: `a=1, b=2, f(n)=20 \in 0(1)` -> `T(n) \in 0(log n)`.

The algorithm runs so fast that individual measurements are unreliable. The program 
executed the search **millions of times**, measured total elapsed time, then divided to 
isolate a single execution. Array sizes use **multiplicative increments (x2)** instead of
linear ones, to ensure each step crosses a new power of 2 and avoids staircase artifacts in
the regresion. 

### Results
Experimental data fits a logarithmic regresion curve with **R² \approx 0.9828**, confirming 
the theoretical model.
