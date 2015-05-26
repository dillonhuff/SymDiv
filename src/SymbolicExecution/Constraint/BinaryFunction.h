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

  bool isBinaryFunction() const override { return true; }
  bool operator==(const Term* other) const override;

  const Term* getRhs() const { return rhs; }
  const Term* getLhs() const { return lhs; }

  std::string toString() const override;
};

#endif
