#ifndef SYMBOL_H
#define SYMBOL_H

#include "SymbolicExecution/Constraint/Term.h"

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
  Symbol& operator=(const Symbol& other) { t = other.t; id = other.id; return *this; }

  virtual bool isSymbol() const { return true; }
  virtual bool operator==(const Term& other) const;
  virtual bool operator==(const Term* other) const;
  virtual bool operator<(const Symbol& other) const { return id < other.id; }
};

#endif
