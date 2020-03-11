#ifndef TRADEMETRICS_CSVTRADEPARSER_H
#define TRADEMETRICS_CSVTRADEPARSER_H

#include "TradeMetrics/TradeFeed.h"

#include <istream>

namespace TradeMetrics {

class CSVParser : public TradeFeed {
public:
  CSVParser(std::istream &IS) : IS(IS) {}

  bool empty() const override { return true; }

  Trade next() override { return Trade(); }

private:
  std::istream &IS;
};

} // namespace TradeMetrics

#endif