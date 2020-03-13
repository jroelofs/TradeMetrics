#ifndef TRADEMETRICS_METRICS_H
#define TRADEMETRICS_METRICS_H

#include "TradeMetrics/MetricsEngine.h"

#include <set>
#include <unordered_map>

namespace TradeMetrics {

struct Metric {
  virtual void publish(Trade T) = 0;
};

struct AllSymbolsMetric : public Metric {
  void publish(Trade T) override {
    Symbols.insert(T.Symbol);
  }
  std::set<SymbolName> Symbols;
};

struct MaxGapMetric : public Metric {
  struct Info {
    int64_t TimeStamp;
    int64_t MaxGap;
  };
  void publish(Trade T) override {
    auto I = Gaps.find(T.Symbol);
    if (I != Gaps.end()) {
      if (T.TimeStamp - I->second.TimeStamp > I->second.MaxGap) {
        I->second.MaxGap = T.TimeStamp - I->second.TimeStamp;
        I->second.TimeStamp = T.TimeStamp;
      }
    } else {
      Gaps.insert({T.Symbol, { T.TimeStamp, 0 }});
    }
  }
  int64_t maxGap(SymbolName S) const {
    auto I = Gaps.find(S);
    if (I == Gaps.end())
      return 0;
    return I->second.MaxGap;
  }
  std::unordered_map<SymbolName, Info> Gaps;
};

struct TotalVolumeMetric : public Metric {
  void publish(Trade T) override {
    Volume[T.Symbol] += T.Quantity;
  }
  int64_t volume(SymbolName S) const {
    auto I = Volume.find(S);
    if (I == Volume.end())
      return 0;
    return I->second;
  }
  std::unordered_map<SymbolName, int64_t> Volume;
};

struct MaxPriceMetric : public Metric {
  void publish(Trade T) override {
    MaxPrice[T.Symbol] = std::max(MaxPrice[T.Symbol], T.Price);
  }
  int64_t maxPrice(SymbolName S) const {
    auto I = MaxPrice.find(S);
    if (I == MaxPrice.end())
      return 0;
    return I->second;
  }
  std::unordered_map<SymbolName, int64_t> MaxPrice;
};

struct WeightedAveragePriceMetric : public Metric {
  struct Info {
    int64_t Volume;
    int64_t Quantity;
  };
  void publish(Trade T) override {
    Sum[T.Symbol].Volume += T.Quantity * T.Price;
    Sum[T.Symbol].Quantity += T.Quantity;
  }
  int64_t avgPrice(SymbolName S) const {
    auto I = Sum.find(S);
    if (I == Sum.end())
      return 0;
    return I->second.Volume / I->second.Quantity;
  }
  std::unordered_map<SymbolName, Info> Sum;
};

} // namespace TradeMetrics

#endif