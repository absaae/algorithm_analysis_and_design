## Practice 4 - Binary Number Product

Analysis and comparision of four algorithms for multiplying two numbers represented as bit arrays.


### Algorithms 

1. **Base** - Simulates binary multiplication using shifts and additions over a 2n array.
2. **Optimized base** - Skips operations when the multiplier bit is 0.
3. **Shift multiplicand** - Eliminates the auxiliary array, shifting M directly each iteration.
4. **Repeated addition** - Computes the product by accumulating b sums of a.

### Complexity

Algorithm      Best case      Worst case  
Base            O(n^2)          O(n^2)\
Omptimized      O(n)            O(n^2)\
Shift M         O(n^2)          O(n^2)\
Repeated sum    O(n)            O(2^n)
