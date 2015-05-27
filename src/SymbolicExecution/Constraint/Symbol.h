#ifndef SYMBOL_H
#define SYMBOL_H

#include "SymbolicExecution/Constraint/Term.h"
#include "SymbolicExecution/Type/Type.h"

#include <iostream>

enum SymbolType {
  INT_32,
  PTR
};

class Symbol : public Term {
 protected:
  const Type* t;
  int id;

 public:
  virtual ~Symbol() {}
  Symbol(const Type* st, int i) { t = st; id = i; kind = SYMBOL; }

  bool operator==(const Term* other) const override;
  
  std::string toString() const override { return "$" + std::to_string((long long int) id); }
};

#endif
