#ifndef Z3_SOLVER_H
#define Z3_SOLVER_H

#include "SymbolicExecution/ConstraintSolver.h"

class Z3Solver : public ConstraintSolver {
 public:
  virtual bool implies(vector<Constraint*> state, Constraint* c);
};

#endif
