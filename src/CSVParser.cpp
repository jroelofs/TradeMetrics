#include "TradeMetrics/CSVParser.h"

using namespace TradeMetrics;

bool CSVParser::empty() const {
  IS.peek();
  return IS.eof();
}

static void malformedInput() {
  // This really deserves better error handling, but for brevity, we just kill
  // the process for now. In a "real" implementation, it would probably be a
  // good idea to keep track of line & column information, for proper
  // diagnostics.
  abort();
}

Trade CSVParser::next() {
  Trade T;
  std::string Data;

  if (!std::getline(IS, Data, ',')) { malformedInput(); }
  T.TimeStamp = std::stoll(Data);

  if (!std::getline(IS, Data, ',')) { malformedInput(); }
  if (Data.size() > 3) { malformedInput(); }
  T.Symbol = Data;

  if (!std::getline(IS, Data, ',')) { malformedInput(); }
  T.Quantity = std::stoll(Data);

  if (!std::getline(IS, Data, '\n')) { malformedInput(); }
  T.Price = std::stoll(Data);

  return T;
} 