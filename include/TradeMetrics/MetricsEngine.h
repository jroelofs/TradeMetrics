#ifndef TRADEMETRICS_METRICSENGINE_H
#define TRADEMETRICS_METRICSENGINE_H

#include <ostream>

class TradeFeed;

namespace TradeMetrics {

class MetricsEngine {
public:
  MetricsEngine(TradeFeed &TF) : TF(TF) {}

  void run();

  void reportCSV(std::ostream &OS) const;

private:
  TradeFeed &TF;
};

} // namespace TradeMetrics

#endif