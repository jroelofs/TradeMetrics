#ifndef TRADEMETRICS_CSVTRADEPARSER_H
#define TRADEMETRICS_CSVTRADEPARSER_H

#include "TradeMetrics/TradeFeed.h"

#include <istream>

namespace TM {

class CSVParser : public TradeFeed {
public:
  CSVParser(std::istream &IS) : IS(IS) {}

  bool empty() const override;
  Trade next() override;

private:
  std::istream &IS;
};

} // namespace TM

#endif