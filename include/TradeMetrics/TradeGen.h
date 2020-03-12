#ifndef TRADEMETRICS_TRADEGEN_H
#define TRADEMETRICS_TRADEGEN_H

#include "TradeMetrics/TradeFeed.h"

#include <memory>

namespace TradeMetrics {

static constexpr char Alphabet[] = "abcdefghijklmnopqrstuvwxyz";
static constexpr int ALen = sizeof(Alphabet) - 1;

std::unique_ptr<TradeFeed> MakeTradeGen(int64_t NumTrades, int NumSymbols);

} // namespace TradeMetrics

#endif