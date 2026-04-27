## Practice - Greedy Algorithms: Change-Making

Implementation and analysis of a greedy algorithm for making change using the minimum numbre of coins,
tested across two scenatios and five selection strategies.


### Problem

Given a target amount, return the exact change using as few coing as possible form a set of available
denominations. 

### Coin Set
<img width="418" height="68" alt="image" src="https://github.com/user-attachments/assets/b67a584a-8b4f-4922-887e-441ed6c51b9d" />

### Scenarios

- **Infinite coins** - No quantity restrictions per denomination.
- **Finite coins** - Limited stock as shown in the table above.

### Selection Strategies

1. **Lowest value** - Always pick the smallest denomination.
2. **Highest value** - Always pick the largest denomiation.
3. **Most available** - Pick the denomination with the most units left.
4. **Least available** - Pick the denomination with the fewest units left.
5. **Closest match** - Pick the denominatino nearest to the remaining amount.

### Test Cases
Amounts tested: **$13, $56, $79, $94**

Note: Some strategies under the finite scenario may fail to find a valid solution depending on the 
amount(e.g., lowest value for $94).


### Takeaway

The selection criterion significantly impacts both the number of coins used and wheter a valid solution
is even reachable. Greedy aproaches are not always optimal - their effectiveness depends heavily on the 
constraints and the chosen srategy.
