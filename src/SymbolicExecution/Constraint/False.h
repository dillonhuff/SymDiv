#ifndef FALSE_H
#define FALSE_H

#include "SymbolicExecution/Constraint/Constraint.h"

class False : public Constraint {
 public:
  False() {
    kind = FALSE;
  }

  bool isFalse() const override { return true; }
  std::string toString() const override { return "false"; }
};

#endif
