#ifndef BINARY_PREDICATE_H
#define BINARY_PREDICATE_H

#include "SymbolicExecution/Constraint/Constraint.h"
#include "SymbolicExecution/Constraint/Term.h"

class BinaryPredicate : public Constraint {
 protected:
  const Term* lhs;
  const Term* rhs;

 public:
  BinaryPredicate(const Term* l, const Term* r)
    : lhs(l), rhs(r) {
    kind = EQ;
  }

  virtual bool isBinaryPredicate() const { return true; }

  virtual bool operator==(const Constraint& other) const;
};

#endif
