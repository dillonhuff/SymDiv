#ifndef BINARY_FUNCTION_H
#define BINARY_FUNCTION_H

#include "SymbolicExecution/Constraint/Term.h"

class BinaryFunction : public Term {
 protected:
  const Term* lhs;
  const Term* rhs;

 public:
  BinaryFunction(const Term* l, const Term* r)
    : lhs(l), rhs(r) {}

  virtual bool isBinaryFunction() const { return true; }

  virtual bool operator==(const Term* other) const;
};

#endif
