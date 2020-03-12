#ifndef TRADEMETRICS_TRADEFEED_H
#define TRADEMETRICS_TRADEFEED_H

#include "TradeMetrics/Trade.h"

namespace TradeMetrics {

class TradeFeed {
public:
  virtual bool empty() const = 0;
  virtual Trade next() = 0;
};

} // namespace TradeMetrics

#endif