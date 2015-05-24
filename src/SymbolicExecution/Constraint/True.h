#ifndef TRUE_H
#define TRUE_H

#include "SymbolicExecution/Constraint/Constraint.h"

class True : public Constraint {
 public:
  True() {
    kind = TRUE;
  }
};

#endif
