#include "TradeMetrics/Metrics.h"

#include "gtest/gtest.h"

#include <array>

using namespace TradeMetrics;

TEST(Metrics, AllSymbolsMetric) {
  AllSymbolsMetric ASM;

  ASM.publish({3, "aac", 3, 3});
  ASM.publish({1, "aaa", 1, 1});
  ASM.publish({2, "aab", 2, 2});

  std::array<SymbolName, 3> Expected{"aaa", "aab", "aac"};
  EXPECT_TRUE(std::equal(begin(Expected), end(Expected), begin(ASM.Symbols)));
}

TEST(Metrics, MaxTimeGap) {
  MaxGapMetric MGM;

  MGM.publish({100, "btc", 10, 5954});
  MGM.publish({100, "ltc", 500, 33});
  MGM.publish({110, "ltc", 320, 34});

  EXPECT_EQ(MGM.maxGap("btc"), 0);
  EXPECT_EQ(MGM.maxGap("ltc"), 10);
}

TEST(Metrics, TotalVolumeTraded) {
  TotalVolumeMetric TVM;

  TVM.publish({10, "cat", 3000, 89});
  TVM.publish({15, "cat", 1500, 90});
  TVM.publish({17, "spx", 42, 2561});

  EXPECT_EQ(TVM.volume("cat"), 4500);
  EXPECT_EQ(TVM.volume("spx"), 42);
}

TEST(Metrics, MaxTradePrice) {
  MaxPriceMetric MPM;

  MPM.publish({1, "btc", 200000000000, 80000}); // lol
  MPM.publish({2, "btc", 14260000000, 6016});

  EXPECT_EQ(MPM.maxPrice("btc"), 80000);
}

TEST(Metrics, WeightedAveragePrice) {
  WeightedAveragePriceMetric WAPM;

  WAPM.publish({1, "aaa", 20, 18});
  WAPM.publish({2, "aaa", 5, 7});

  EXPECT_EQ(WAPM.avgPrice("aaa"), 15);
}