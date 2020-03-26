#include "TradeMetrics/Metrics.h"
#include "TradeMetrics/MetricsEngine.h"
#include "TradeMetrics/TradeFeed.h"

#include <benchmark/benchmark.h>

using namespace TM;

template<typename Metric>
static void BM_SingleMetric(benchmark::State &State) {
  std::unique_ptr<TradeFeed> RTF = CreateRandomTradeFeed(-1, 25);
  Metric M;
  for (auto _ : State) {
    for (int I = 0, E = State.iterations(); I != E; ++I) {
      M.publish(RTF->next());
    }
  }
}
BENCHMARK_TEMPLATE(BM_SingleMetric, AllSymbolsMetric);
BENCHMARK_TEMPLATE(BM_SingleMetric, MaxGapMetric);
BENCHMARK_TEMPLATE(BM_SingleMetric, TotalVolumeMetric);
BENCHMARK_TEMPLATE(BM_SingleMetric, MaxPriceMetric);
BENCHMARK_TEMPLATE(BM_SingleMetric, WeightedAveragePriceMetric);

BENCHMARK_MAIN();