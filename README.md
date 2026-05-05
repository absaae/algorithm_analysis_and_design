## Sortings Algorithms Analysis

Experimental and theoretical analysis of three sorting algorithms, studying execution time
T(n,k) where n is the array size and k is the number of initially sorted elements(first half
sorted, second half unsorted).

### Algorithms

1. **Bubble sort**: Compares adjacent pairs and swaps them if out of order; repeats until fully sorted.
2. **Insertion sort**: Picks each element and places it in its correct position within the already-sorted position.
3. **Selection sort**: Finds the minimum element each iteration and places it in its final position.

### Results

<img width="1154" height="167" alt="Captura desde 2026-05-05 11-20-50" src="https://github.com/user-attachments/assets/2c888470-0e25-4c1d-b63e-8e58e1da97e2" />\


Bubble sort when fixed n and varying k, the executio time decreasses linearly so -> fitted
with linear regresion. 

Insertion sort when dixed n and varying k, the time follows a decreasing parabola so -> fitted
with degree-2 polynomial regression.

Selection sort in the best and worst case curves are virtually identical, confirminf that
initial orden has no impact on its performance. 

All three algorithms share O(n²) worst-case complexity, but behave very differently when
the input is partially sorted. Bubble and Insertion sort can exploit prior orden; Selection
sort cannot - it always does the same amount of work regardless of the input state. 
