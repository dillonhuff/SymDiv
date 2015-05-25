#ifndef MINUS_H
#define MINUS_H

#include "SymbolicExecution/Constraint/BinaryFunction.h"

class Minus : public BinaryFunction {
 public:
  Minus(const Term* l, const Term* r)
    : BinaryFunction::BinaryFunction(l, r) {
    kind = MINUS;
  }

  virtual bool isMinus() const { return true; }

  virtual bool operator==(const Term* other) const {
    return BinaryFunction::operator==(other); 
  }
};

#endif
