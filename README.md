## Practice - Execution Time: Character Search in Square MAtrix

Analysis of execution time for a character search algorithm over dynamically allocates square
matrices('char'), tested across three scenarios and multiple matrix sizes. 

### Matrix sizes
500 x 500\
1000 x 1000\
...\
10000 x 10000

### Scenarios

- **Best case**: The target character is absent form the entire matrix.
- **Worst case**: Every cell contains the target character.
- **Average case**: Both the matrix contents and the targert character are randomly generated.

Each size/scenario combination was executed **150 times** to reduce variance. Time was measured
with 'clock()', and results were analyzed in Python using **second-degree polynomial regresion**.

### Complexity

All three scenarios yield **0(n²)** - the algorithm always traverses the full nxn matrix
regardless of the case. 
