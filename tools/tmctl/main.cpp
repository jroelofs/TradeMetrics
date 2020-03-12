#include "TradeMetrics/CSVParser.h"
#include "TradeMetrics/MetricsEngine.h"
#include "TradeMetrics/Metrics.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace TradeMetrics;

static void usage() {
  std::cerr << "usage:\n"
            << "\ttmctl input.csv > output.csv\n"
            << "\tcat input.csv | tmctl - > output.csv\n";
  exit(-1);
}

static void go(std::istream &IS, std::ostream &OS) {
  CSVParser P(std::cin);
  MetricsEngine ME(P);

  AllSymbolsMetric ASM;
  ME.enroll(&ASM);

  MaxGapMetric MGM;
  ME.enroll(&MGM);

  TotalVolumeMetric TVM;
  ME.enroll(&TVM);

  MaxPriceMetric MPM;
  ME.enroll(&MPM);

  WeightedAveragePriceMetric WAPM;
  ME.enroll(&WAPM);

  ME.run();

  for (const auto &Symbol : ASM.Symbols) {
    OS << Symbol << ','
       << MGM.maxGap(Symbol) << ','
       << TVM.volume(Symbol) << ','
       << MPM.maxPrice(Symbol) << ','
       << WAPM.avgPrice(Symbol) << '\n';
  }
}

int main(int argc, char **argv) {
  if (argc != 2 || std::string("-h") == argv[1] ||
      std::string("--help") == argv[1]) {
    usage();
    return -1;
  }

  // Input via pipe.
  if (std::string("-") == argv[1]) {
    go(std::cin, std::cout);
    return 0;
  }

  // Input via command-line specified file.
  std::ifstream InFile(argv[1]);
  if (!InFile.is_open()) {
    std::cerr << "Could not open file";
    return -1;
  }

  go(InFile, std::cout);
  return 0;
}
