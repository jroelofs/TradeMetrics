#include "TradeMetrics/Metrics.h"
#include "TradeMetrics/MetricsEngine.h"
#include "TradeMetrics/TradeFeed.h"

#include <benchmark/benchmark.h>

using namespace TM;

static void BM_AllMetrics(benchmark::State &State) {
  for (auto _ : State) {
    State.PauseTiming();

    std::unique_ptr<TradeFeed> RTF = CreateRandomTradeFeed(State.iterations(), State.range(0));

    MetricsEngine ME(*RTF);

    AllSymbolsMetric ASM;
    ME.enroll(&ASM);

    MaxGapMetric MGM;
    ME.enroll(&MGM);

    TotalVolumeMetric TVM;
    ME.enroll(&TVM);

    MaxPriceMetric MPM;
    ME.enroll(&MPM);

    WeightedAveragePriceMetric WAPM;
    ME.enroll(&WAPM);

    State.ResumeTiming();

    ME.run();
  }
}
BENCHMARK(BM_AllMetrics)->Range(8, 8<<10);

template<typename Metric>
static void BM_SingleMetric(benchmark::State &State) {
  for (auto _ : State) {
    State.PauseTiming();

    std::unique_ptr<TradeFeed> RTF = CreateRandomTradeFeed(State.iterations(), State.range(0));

    Metric M;

    State.ResumeTiming();

    while (!RTF->empty()) {
      M.publish(RTF->next());
    }
  }
}
BENCHMARK_TEMPLATE(BM_SingleMetric, AllSymbolsMetric)->Range(4, 8<<10);
BENCHMARK_TEMPLATE(BM_SingleMetric, MaxGapMetric)->Range(4, 8<<10);
BENCHMARK_TEMPLATE(BM_SingleMetric, TotalVolumeMetric)->Range(4, 8<<10);
BENCHMARK_TEMPLATE(BM_SingleMetric, MaxPriceMetric)->Range(4, 8<<10);
BENCHMARK_TEMPLATE(BM_SingleMetric, WeightedAveragePriceMetric)->Range(4, 8<<10);

BENCHMARK_MAIN();