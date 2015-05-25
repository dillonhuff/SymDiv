#ifndef MINUS_H
#define MINUS_H

#include "SymbolicExecution/Constraint/BinaryFunction.h"

class Minus : public BinaryFunction {
 public:
  Minus(const Term* l, const Term* r)
    : BinaryFunction::BinaryFunction(l, r) {
    kind = MINUS;
  }

  virtual bool isMinus() const override { return true; }

  bool operator==(const Term* other) const override {
    return BinaryFunction::operator==(other); 
  }
};

#endif
