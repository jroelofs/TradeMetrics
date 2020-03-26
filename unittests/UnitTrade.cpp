#include "TradeMetrics/Trade.h"

#include "gtest/gtest.h"

using namespace TM;

TEST(SymbolName, Equality) {
  EXPECT_EQ(SymbolName("aaa"), SymbolName(0));
  EXPECT_EQ(SymbolName("aaa"), 0);
  EXPECT_EQ(SymbolName(0), "aaa");
}

TEST(SymbolName, IntSerialization) {
  EXPECT_EQ(SymbolName("aaa"), 0);
  EXPECT_EQ(SymbolName("baa"), 1);
  EXPECT_EQ(SymbolName("zzz"), 26 * 26 * 26 - 1);
  EXPECT_EQ(SymbolName("xyz"), ('x'-'a') + ('y'-'a') * 26 + ('z'-'a') * 26 * 26);
}