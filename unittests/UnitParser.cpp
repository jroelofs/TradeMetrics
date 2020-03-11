#include "TradeMetrics/CSVParser.h"
#include "TradeMetrics/Trade.h"

#include "gtest/gtest.h"

using namespace TradeMetrics;

TEST(Parsing, OneLine) {
  // 10 shares of aaa stock at a price of 12
  std::stringstream SS("1234567,aaa,10,12");

  CSVParser Feed(SS);

  ASSERT_FALSE(Feed.empty());

  Trade T1 = Feed.next();
  EXPECT_EQ(T1.TimeStamp, 1234567);
  EXPECT_EQ(T1.Symbol, "aaa");
  EXPECT_EQ(T1.Quantity, 10);
  EXPECT_EQ(T1.Price, 12);
}