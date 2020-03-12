#include "TradeMetrics/CSVParser.h"
#include "TradeMetrics/MetricsEngine.h"
#include "TradeMetrics/Metrics.h"

#include "gtest/gtest.h"

using namespace TradeMetrics;

TEST(MetricsEngine, Sample) {
  // clang-format off
  std::stringstream SS(
    "52924702,aaa,13,1136\n"
    "52924702,aac,20,477\n"
    "52925641,aab,31,907\n"
    "52927350,aab,29,724\n"
    "52927783,aac,21,638\n"
    "52930489,aaa,18,1222\n"
    "52931654,aaa,9,1077\n"
    "52933453,aab,9,756"
  );
  // clang-format on

  CSVParser Feed(SS);
  MetricsEngine ME(Feed);

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

  ME.run();

  struct {
    char Symbol[4];
    int64_t MaxTimeGap;
    int64_t Volume;
    int64_t WeightedAveragePrice;
    int64_t MaxPrice;
  } Expected[] = {
    {"aaa", 5787, 40, 1161, 1222},
    {"aab", 6103, 69,  810,  907},
    {"aac", 3081, 41,  559,  638},
  };

  for (const auto &E : Expected) {
    EXPECT_EQ(MGM.maxGap(E.Symbol), E.MaxTimeGap);
    EXPECT_EQ(TVM.volume(E.Symbol), E.Volume);
    EXPECT_EQ(WAPM.avgPrice(E.Symbol), E.WeightedAveragePrice);
    EXPECT_EQ(MPM.maxPrice(E.Symbol), E.MaxPrice);
  }
}