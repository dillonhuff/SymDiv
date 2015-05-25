#ifndef EQ_H
#define EQ_H

#include "SymbolicExecution/Constraint/BinaryPredicate.h"
#include "SymbolicExecution/Constraint/Term.h"

#include <iostream>

using namespace std;

class Eq : public BinaryPredicate {
 public:
  Eq(const Term* l, const Term* r)
    : BinaryPredicate::BinaryPredicate(l, r) {
    kind = EQ;
  }

  virtual bool operator==(const Constraint* other) const {
    return BinaryPredicate::operator==(other);
  }

  virtual bool isEq() const { return true; }

};

#endif
