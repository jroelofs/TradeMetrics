#ifndef TRADEMETRICS_TRADE_H
#define TRADEMETRICS_TRADE_H

#include <ostream>
#include <cinttypes>

namespace TradeMetrics {

struct Trade {
  int64_t TimeStamp;
  char Symbol[4];
  int64_t Quantity;
  int64_t Price;
};

inline std::ostream &operator<<(std::ostream &OS, Trade T) {
  return OS << T.TimeStamp << ',' << T.Symbol << ',' << T.Quantity << ',' << T.Price;
}

} // namespace TradeMetrics

#endif