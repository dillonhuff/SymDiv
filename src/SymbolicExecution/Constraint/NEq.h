#ifndef NEQ_H
#define NEQ_H

#include "SymbolicExecution/Constraint/BinaryPredicate.h"
#include "SymbolicExecution/Constraint/Term.h"

#include <iostream>

using namespace std;

class NEq : public BinaryPredicate {
 public:
  NEq(const Term* l, const Term* r)
    : BinaryPredicate::BinaryPredicate(l, r) {
    kind = NEQ;
  }
};

#endif
