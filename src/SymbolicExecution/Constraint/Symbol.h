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
  Symbol(SymbolType st, int i) { t = st; id = i; }

  virtual bool isSymbol() const { return true; }
  virtual bool operator==(const Term* other) const;
  
  virtual std::string toString() { return "$" + std::to_string((long long int) id); }
};

#endif
