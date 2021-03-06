#ifndef TRADEMETRICS_TRADE_H
#define TRADEMETRICS_TRADE_H

#include <ostream>
#include <cinttypes>

namespace TM {

struct SymbolName {
  SymbolName() : Val(0) {}
  SymbolName(int32_t Val) : Val(Val) {}
  SymbolName(const std::string &S) {
    Val = (S[0] - 'a') + (S[1] - 'a') * 26 + (S[2] - 'a') * 26 * 26;
  }
  SymbolName(const char (&S)[4]) {
    Val = (S[0] - 'a') + (S[1] - 'a') * 26 + (S[2] - 'a') * 26 * 26;
  }

  bool operator==(SymbolName RHS) const { return Val == RHS.Val; }
  bool operator==(int32_t RHS) const { return Val == RHS; }
  operator int32_t() const { return Val; }
  operator std::string() const {
    int Lo = Val % 26;
    int Mid = ((Val - Lo) / 26) % 26;
    int Hi = (Val - Mid * 26 - Lo) / 26 / 26;
    return { char(Lo + 'a'), char(Mid + 'a'), char(Hi + 'a') };
  }

  int32_t Val;
};

inline std::ostream &operator<<(std::ostream &OS, SymbolName S) {
  return OS << (std::string)S;
}

struct Trade {
  int64_t TimeStamp;
  SymbolName Symbol;
  int64_t Quantity;
  int64_t Price;
};

inline std::ostream &operator<<(std::ostream &OS, Trade T) {
  return OS << T.TimeStamp << ',' << T.Symbol << ',' << T.Quantity << ',' << T.Price;
}

} // namespace TM

namespace std {
  template <> struct hash<TM::SymbolName> {
    size_t operator()(TM::SymbolName S) const {
      return hash<int32_t>()(S.Val);
    }
  };
}

#endif