#ifndef CONSTRAINT_SOLVER_H
#define CONSTRAINT_SOLVER_H

#include "SymbolicExecution/Constraint/Constraint.h"

#include <vector>

using namespace std;

class ConstraintSolver {
 public:
  virtual ~ConstraintSolver() {}

  virtual bool constraintsImply(vector<Constraint*>* state, Constraint* c) { return false; }
  virtual bool constraintsAllow(vector<Constraint*>* state, Constraint* c) { return false; }
};

#endif
