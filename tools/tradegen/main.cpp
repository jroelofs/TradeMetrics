#include "TradeMetrics/TradeGen.h"

#include <iostream>
#include <memory>

using namespace TradeMetrics;

static void usage() {
  std::cerr << "usage:\n"
            << "\ttradegen <N> <S>\n"
            << "\t\tN: number of trades to generate\n"
            << "\t\tS: number of unique symbols\n";
}

int main(int argc, char **argv) {
  if (argc != 3) {
    usage();
    return -1;
  }

  long long NumTrades = std::stoll(argv[1]);
  int SymbolCount = std::stoi(argv[2]);

  if (SymbolCount > ALen * ALen * ALen) {
    std::cerr << "error: not enough symbols in alphabet^3\n";
    return -1;
  }

  std::unique_ptr<TradeFeed> TG = MakeTradeGen(NumTrades, SymbolCount);

  while (!TG->empty()) {
    std::cout << TG->next() << '\n';
  }

  return 0;
}