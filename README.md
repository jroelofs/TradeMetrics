## TradeMetrics

Calculates metrics on a series of trades, input in csv format.

### Build

```sh
git clone git@github.com:jroelofs/TradeMetrics.git
mkdir build && cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ../TradeMetrics
cd build
ninja
```

### Run

```sh
$ tmctl input.csv > output.csv
```

### Test

```sh
$ ninja check
```
