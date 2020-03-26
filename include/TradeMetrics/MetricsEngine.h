#ifndef TRADEMETRICS_METRICSENGINE_H
#define TRADEMETRICS_METRICSENGINE_H

#include "TradeMetrics/Trade.h"
#include "TradeMetrics/Metrics.h"

#include <memory>
#include <ostream>
#include <vector>
#include <iosfwd>

namespace TM {

class TradeFeed;

class Metric;

class MetricsEngine {
public:
  MetricsEngine(TradeFeed &TF);

  void run();

  void enroll(Metric *M);

  auto begin() const { return Metrics.cbegin(); }
  auto end() const { return Metrics.cend(); }

  void report(std::ostream &OS) const;

private:
  std::unique_ptr<Metric> ASM;
  std::vector<Metric*> Metrics;
  TradeFeed &TF;
};

} // namespace TM

#endif