#include "TradeMetrics/MetricsEngine.h"

#include "TradeMetrics/Trade.h"
#include "TradeMetrics/TradeFeed.h"
#include "TradeMetrics/Metrics.h"

#include <ostream>
#include <utility>

using namespace TM;

MetricsEngine::MetricsEngine(TradeFeed &TF)
    : TF(TF), ASM(std::make_unique<AllSymbolsMetric>())
{
}

void MetricsEngine::run() {
  while (!TF.empty()) {
    Trade T = TF.next();
    ASM->publish(T);
    for (auto &M : Metrics) {
      M->publish(T);
    }
  }
}

void MetricsEngine::enroll(Metric *M) {
  Metrics.push_back(M);
}

void MetricsEngine::report(std::ostream &OS) const {
  const AllSymbolsMetric &ASM = static_cast<const AllSymbolsMetric&>(*this->ASM);
  for (size_t I = 0, E = ASM.Symbols.size(); I != E; ++I) {
    if (ASM.Symbols[I]) {
      SymbolName Symbol(I);
      OS << Symbol;
      for (Metric *M : std::as_const(*this)) {
        if (M != &ASM) {
          M->print(OS << ",", SymbolName(I));
        }
      }
      OS << "\n";
    }
  }
}