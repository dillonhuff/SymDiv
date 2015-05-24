#ifndef PLUS_H
#define PLUS_H

#include "SymbolicExecution/Constraint/BinaryFunction.h"

class Plus : public BinaryFunction {
 public:
  Plus(const Term* l, const Term* r)
    : BinaryFunction::BinaryFunction(l, r) {
    kind = PLUS;
  }

  virtual bool operator==(const Term* other) const {
    return BinaryFunction::operator==(other);
  }
};

#endif
