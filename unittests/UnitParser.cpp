#include "TradeMetrics/CSVParser.h"
#include "TradeMetrics/Trade.h"

#include "gtest/gtest.h"

using namespace TM;

TEST(Parsing, OneLine) {
  // 10 shares of aaa stock at a price of 12
  std::stringstream SS("1234567,aaa,10,12");

  CSVParser Feed(SS);

  ASSERT_FALSE(Feed.empty());

  Trade T1 = Feed.next();
  EXPECT_EQ(T1.TimeStamp, 1234567);
  EXPECT_EQ(T1.Symbol, std::string("aaa"));
  EXPECT_EQ(T1.Quantity, 10);
  EXPECT_EQ(T1.Price, 12);

  ASSERT_TRUE(Feed.empty());
}

TEST(Parsing, MultiLine) {
  // clang-format off
  std::stringstream SS(
    "1,aaa,10,12\n"
    "2,bbb,42,37");
  // clang-format on

  CSVParser Feed(SS);

  ASSERT_FALSE(Feed.empty());

  Trade T1 = Feed.next();
  EXPECT_EQ(T1.TimeStamp, 1);
  EXPECT_EQ(T1.Symbol, std::string("aaa"));

  Trade T2 = Feed.next();
  EXPECT_EQ(T2.TimeStamp, 2);
  EXPECT_EQ(T2.Symbol, std::string("bbb"));

  ASSERT_TRUE(Feed.empty());
}