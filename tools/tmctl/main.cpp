#include "TradeMetrics/CSVParser.h"
#include "TradeMetrics/MetricsEngine.h"

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

int main(int argc, char **argv) {
  if (argc != 2 || std::string("-h") == argv[1] ||
      std::string("--help") == argv[1]) {
    usage();
    return -1;
  }

  // Input via pipe.
  if (std::string("-") == argv[1]) {
    CSVParser P(std::cin);
    MetricsEngine ME(P);
    ME.run();
    ME.reportCSV(std::cout);
    return 0;
  }

  // Input via command-line specified file.
  std::ifstream InFile(argv[1]);
  if (!InFile.is_open()) {
    std::cerr << "Could not open file";
    return -1;
  }

  CSVParser P(InFile);
  MetricsEngine ME(P);
  ME.run();
  ME.reportCSV(std::cout);
  return 0;
}
