#ifndef EQ_H
#define EQ_H

#include "SymbolicExecution/Constraint/Constraint.h"
#include "SymbolicExecution/Constraint/Term.h"

class Eq : public Constraint {
 public:
  Eq(const Term& l, const Term& r) {}
};

#endif
