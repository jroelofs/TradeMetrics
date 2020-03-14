#ifndef TRADEMETRICS_METRICS_H
#define TRADEMETRICS_METRICS_H

#include "TradeMetrics/MetricsEngine.h"

#include <set>
#include <unordered_map>

namespace TM {

struct Metric {
  virtual void publish(Trade T) = 0;
  virtual ~Metric() {}
};

struct AllSymbolsMetric : public Metric {
  AllSymbolsMetric() : Symbols(26*26*26, false) {}
  void publish(Trade T) override {
    Symbols[T.Symbol] = true;
  }
  std::vector<bool> Symbols;
};

struct MaxGapMetric : public Metric {
  MaxGapMetric() : Gaps(26*26*26, {0,0}) {}
  struct Info {
    int64_t TimeStamp;
    int64_t MaxGap;
  };
  void publish(Trade T) override {
    if (Gaps[T.Symbol].TimeStamp != 0) {
      if (T.TimeStamp - Gaps[T.Symbol].TimeStamp > Gaps[T.Symbol].MaxGap) {
        Gaps[T.Symbol].MaxGap = T.TimeStamp - Gaps[T.Symbol].TimeStamp;
        Gaps[T.Symbol].TimeStamp = T.TimeStamp;
      }
    } else {
      Gaps[T.Symbol].TimeStamp = T.TimeStamp;
      Gaps[T.Symbol].MaxGap = 0;
    }
  }
  int64_t maxGap(SymbolName S) const {
    return Gaps[S].MaxGap;
  }
  std::vector<Info> Gaps;
};

struct TotalVolumeMetric : public Metric {
  TotalVolumeMetric() : Volume(26*26*26, 0) {}
  void publish(Trade T) override {
    Volume[T.Symbol] += T.Quantity;
  }
  int64_t volume(SymbolName S) const {
    return Volume[S];
  }
  std::vector<int64_t> Volume;
};

struct MaxPriceMetric : public Metric {
  MaxPriceMetric() : MaxPrice(26*26*26, 0) {}
  void publish(Trade T) override {
    MaxPrice[T.Symbol] = std::max(MaxPrice[T.Symbol], T.Price);
  }
  int64_t maxPrice(SymbolName S) const {
    return MaxPrice[S];
  }
  std::vector<int64_t> MaxPrice;
};

struct WeightedAveragePriceMetric : public Metric {
  WeightedAveragePriceMetric() : Sum(26*26*26, {0,0}) {}
  struct Info {
    int64_t Volume;
    int64_t Quantity;
  };
  void publish(Trade T) override {
    Sum[T.Symbol].Volume += T.Quantity * T.Price;
    Sum[T.Symbol].Quantity += T.Quantity;
  }
  int64_t avgPrice(SymbolName S) const {
    return Sum[S].Volume / Sum[S].Quantity;
  }
  std::vector<Info> Sum;
};

} // namespace TM

#endif