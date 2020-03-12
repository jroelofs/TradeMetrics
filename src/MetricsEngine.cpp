#include "TradeMetrics/MetricsEngine.h"

#include "TradeMetrics/Trade.h"
#include "TradeMetrics/TradeFeed.h"
#include "TradeMetrics/Metrics.h"

#include <ostream>

using namespace TradeMetrics;

void MetricsEngine::run() {
  while (!TF.empty()) {
    Trade T = TF.next();
    for (auto &M : Metrics) {
      M->publish(T);
    }
  }
}

void MetricsEngine::enroll(Metric *M) {
  Metrics.push_back(M);
}
