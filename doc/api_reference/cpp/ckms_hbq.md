# stmpct::ckms_hbq

Defined in header `<stmpct/ckms_hbq.hpp>`

```cpp
template<
    class ValueT
> class ckms_hbq;
```

`stmpct::ckms_hbq` is a class which implements the Cormode-Korn-Muthukrishnan-Srivastava
streaming percentile algorithm for high-biased quantiles from CKMS05.

`ValueT` is the type of the measurements for which you are calculating percentiles.  It must have the
following properties:
- Assignable
- Default-constructible
- Copy-constructible
- Implements `operator<`

## Member functions

| Function | Description |
| -------- | ----------- |
| `ckms_hbq(double epsilon)` (constructor) | Creates a data structure that can answer approximte high-biased quantile queries about a sequence to within a precision of +/- `epsilon` * (1 - `phi`) * N. |
| `void insert(ValueT v)` | Inserts a measurement into the data structure. |
| `ValueT quantile(double phi) const` | Calculate the `epsilon`-approximate `phi`-quantile for the sequence. |

## Example

```cpp
#include <stmpct/ckms_hbq.hpp>

double epsilon = 0.1;
stmpct::ckms_hbq<double> c(epsilon);
for (int i = 0; i < 1000; ++i)
    c.insert(rand());
double p50 = c.quantile(0.5); // Approx. median
double p95 = c.quantile(0.95); // Approx. 95th percentile
```

## References

CKMS05: G. Cormode, F. Korn, S. Muthukrishnan and D. Srivastava. Effective Computation of Biased Quantiles over Data Streams. In _Proceedings of the 21st International Conference on Data Engineering_, pages 20-31, 2005.