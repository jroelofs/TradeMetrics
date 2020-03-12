#ifndef TRADEMETRICS_METRICSENGINE_H
#define TRADEMETRICS_METRICSENGINE_H

#include "TradeMetrics/Trade.h"

#include <memory>
#include <ostream>
#include <vector>

namespace TradeMetrics {

class TradeFeed;

class Metric;

class MetricsEngine {
public:
  MetricsEngine(TradeFeed &TF) : TF(TF) {}

  void run();

  void enroll(Metric *M);

private:
  std::vector<Metric*> Metrics;
  TradeFeed &TF;
};

} // namespace TradeMetrics

#endif