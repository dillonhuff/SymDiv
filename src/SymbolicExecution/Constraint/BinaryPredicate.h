#ifndef BINARY_PREDICATE_H
#define BINARY_PREDICATE_H

#include "SymbolicExecution/Constraint/Constraint.h"
#include "SymbolicExecution/Constraint/Term.h"

#include <string>

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
  virtual bool operator==(const Constraint* other) const;

  virtual const Term* getLhs() const { return lhs; }
  virtual const Term* getRhs() const { return rhs; }

  virtual std::string toString() const override {
    std::string res = "(";
    res += constraintKindToString(kind) + " ";
    res += lhs->toString() + " ";
    res += rhs->toString();
    res += ")";
    return res;
  }
};

#endif
