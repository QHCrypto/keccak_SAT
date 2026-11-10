## CNF Generation

The `write_cnf` directory contains the code for generating CNF formulas corresponding to three different approaches for constraining non-trivial differential paths.

### Configurable Parameters

The following parameters can be adjusted:

- `width`: The width of the Keccak state.
- `ROUNDS`: The number of rounds modeled, with backward computation of the previous round's weight.
- `limit_k`: The parameter used to limit the total weight of the differential path.
- `mode`: Selects the Boolean cardinality constraint modeling method. Four options are available:
  - `s`
  - `p0`
  - `p1`
  - `p2`
- `loc` (optional): The parameter specifying the constraint location for some non-triviality constraint approaches.

