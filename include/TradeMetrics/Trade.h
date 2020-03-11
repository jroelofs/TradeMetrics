#ifndef TRADEMETRICS_TRADE_H
#define TRADEMETRICS_TRADE_H

#include <cinttypes>

namespace TradeMetrics {

struct Trade {
  int64_t TimeStamp;
  char Symbol[4];
  int32_t Quantity;
  int32_t Price;
};

} // namespace TradeMetrics

#endif