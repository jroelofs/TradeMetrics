#include "TradeMetrics/Metrics.h"
#include "TradeMetrics/MetricsEngine.h"
#include "TradeMetrics/TradeFeed.h"

#include <benchmark/benchmark.h>

using namespace TradeMetrics;

static void BM_MetricsEngine(benchmark::State &State) {
  for (auto _ : State) {
    State.PauseTiming();

    std::unique_ptr<TradeFeed> RTF = CreateRandomTradeFeed(State.iterations(), 10);

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
BENCHMARK(BM_MetricsEngine);

BENCHMARK_MAIN();