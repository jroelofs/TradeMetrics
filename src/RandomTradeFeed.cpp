#include "TradeMetrics/TradeFeed.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace TradeMetrics;

static constexpr int Seed = 42;

static std::vector<std::string> MakeSymbols(int Count) {
  std::vector<std::string> Symbols(Count);
  int I = 0;
  std::generate_n(begin(Symbols), Count, [&I]() -> std::string {
    // First break up I into the base of ALen, which "counts" through each of
    // the letters in Alphabet.
    int Lo = I % ALen;
    int Mid = ((I - Lo) / ALen) % ALen;
    int Hi = (I - Mid * ALen - Lo) / ALen / ALen;

    // Next, as a UX optimization, rotate the latter two letters' starting
    // points to line up with the first's. This helps distinguish Symbols when
    // the count is low, since it generates ones like 'aaa', 'bbb', etc. instead
    // of 'aab', 'aac', etc.
    //
    // For larger Counts, this ends up being a wash, since we end up generating
    // every possible combination anyway.
    Mid = (Mid + Lo) % ALen;
    Hi = (Hi + Lo) % ALen;

    char Sym[4] = {Alphabet[Lo], Alphabet[Mid], Alphabet[Hi], '\0'};
    I++;
    return Sym;
  });
  return Symbols;
}

template <typename Iter, typename RNG>
static Iter RandomElt(Iter I, Iter E, RNG &G) {
  std::uniform_int_distribution<> D(0, std::distance(I, E) - 1);
  std::advance(I, D(G));
  return I;
}

template <typename T, typename RNG> static T RandomVal(T Lo, T Hi, RNG &G) {
  std::uniform_int_distribution<T> D(Lo, Hi - 1);
  return D(G);
}

namespace {

class TradeGen : public TradeFeed {
public:
  TradeGen(int64_t NumTrades, int SymbolCount)
      : NumTrades(NumTrades), TradesPublished(0), Time(0), G(Seed),
        Symbols(MakeSymbols(SymbolCount)) {}

  bool empty() const override { return NumTrades == TradesPublished; }

  Trade next() override {
    Trade T;

    T.TimeStamp = Time += RandomVal<int64_t>(1, 100, G);

    std::string Symbol = *RandomElt(begin(Symbols), end(Symbols), G);
    strlcpy(T.Symbol, Symbol.c_str(), sizeof(T.Symbol));

    T.Quantity = RandomVal<int64_t>(1, 100000, G);
    T.Price = RandomVal<int64_t>(1, 100000, G);

    TradesPublished++;
    return T;
  }

private:
  const int64_t NumTrades;
  int64_t TradesPublished;
  int64_t Time;
  std::mt19937 G;
  std::vector<std::string> Symbols;
};

} // anonymous namespace

std::unique_ptr<TradeFeed> TradeMetrics::CreateRandomTradeFeed(int64_t NumTrades,
                                                               int SymbolCount) {
  return std::make_unique<TradeGen>(NumTrades, SymbolCount);
}
