#ifndef FALSE_H
#define FALSE_H

#include "SymbolicExecution/Constraint/Constraint.h"

class False : public Constraint {
 public:
  False() {
    kind = FALSE;
  }
};

#endif
