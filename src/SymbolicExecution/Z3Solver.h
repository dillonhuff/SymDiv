#ifndef Z3_SOLVER_H
#define Z3_SOLVER_H

#include "SymbolicExecution/ConstraintSolver.h"

#include "z3++.h"

#include <vector>

using namespace std;

class Z3Solver : public ConstraintSolver {
 protected:
  z3::expr toZ3Expr(z3::context* ctx, const Term* t);
  z3::expr toZ3Expr(z3::context* ctx, const Constraint* c);
  z3::expr andConstraints(z3::context* ctx, const vector<Constraint*>* state);
  bool checkSAT(z3::solver s);

 public:
  bool constraintsImply(vector<Constraint*>* state, Constraint* c) override;
  bool constraintsAllow(vector<Constraint*>* state, Constraint* c) override;
};

#endif
