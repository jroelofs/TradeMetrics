#ifndef TRADEMETRICS_TRADEFEED_H
#define TRADEMETRICS_TRADEFEED_H

#include "TradeMetrics/Trade.h"

#include <memory>

namespace TradeMetrics {

class TradeFeed {
public:
  virtual bool empty() const = 0;
  virtual Trade next() = 0;
  virtual ~TradeFeed() {}
};

static constexpr char Alphabet[] = "abcdefghijklmnopqrstuvwxyz";
static constexpr int ALen = sizeof(Alphabet) - 1;

std::unique_ptr<TradeFeed> CreateRandomTradeFeed(int64_t NumTrades, int NumSymbols);

} // namespace TradeMetrics

#endif