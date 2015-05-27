#ifndef SYMBOL_H
#define SYMBOL_H

#include "SymbolicExecution/Constraint/Term.h"

#include <iostream>

enum SymbolType {
  INT_32,
  PTR
};

class Symbol : public Term {
 protected:
  SymbolType t;
  int id;

 public:
  Symbol() { kind = SYMBOL; t = INT_32; id = -1; }
  virtual ~Symbol() {}
  Symbol(SymbolType st, int i) { t = st; id = i; kind = SYMBOL; }

  bool operator==(const Term* other) const override;
  
  std::string toString() const override { return "$" + std::to_string((long long int) id); }
};

#endif
