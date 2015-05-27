#ifndef DIVIDE_H
#define DIVIDE_H

#include "SymbolicExecution/Constraint/BinaryFunction.h"

class Divide : public BinaryFunction {
 public:
  Divide(const Term* l, const Term* r)
    : BinaryFunction::BinaryFunction(l, r) {
    kind = DIVIDE;
  }
  
  bool operator==(const Term* other) const override {
    return BinaryFunction::operator==(other);
  }
};

#endif
