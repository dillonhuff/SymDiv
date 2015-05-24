#ifndef PLUS_H
#define PLUS_H

#include "SymbolicExecution/Constraint/Term.h"

class Plus : public Term {
 public:
  Plus(const Term* l, const Term* r) { kind = PLUS; }
};

#endif
