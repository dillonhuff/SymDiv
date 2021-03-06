#include "SymbolicExecution/Constraint/ConstantInt32.h"
#include "SymbolicExecution/Constraint/Divide.h"
#include "SymbolicExecution/Constraint/Eq.h"
#include "SymbolicExecution/Constraint/Minus.h"
#include "SymbolicExecution/Constraint/NEq.h"
#include "SymbolicExecution/Constraint/Plus.h"
#include "SymbolicExecution/Constraint/Symbol.h"
#include "SymbolicExecution/Constraint/Times.h"
#include "SymbolicExecution/Z3Solver.h"

#include <iostream>

using namespace std;
using namespace z3;

z3::expr Z3Solver::toZ3Expr(z3::context* ctx, const Term* t) {
  if (t->isSymbol()) {
    const Symbol* s = static_cast<const Symbol*>(t);
    return ctx->bv_const(s->toString().c_str(), 32);
  } else if (t->isPlus()) {
    const Plus* tP = static_cast<const Plus*>(t);
    return toZ3Expr(ctx, tP->getLhs()) + toZ3Expr(ctx, tP->getRhs());
  } else if (t->isMinus()) {
    auto tM = static_cast<const Minus*>(t);
    return toZ3Expr(ctx, tM->getLhs()) - toZ3Expr(ctx, tM->getRhs());
  } else if (t->isTimes()) {
    auto tT = static_cast<const Times*>(t);
    return toZ3Expr(ctx, tT->getLhs()) * toZ3Expr(ctx, tT->getRhs());
  } else if (t->isDivide()) {
    auto tD = static_cast<const Divide*>(t);
    return toZ3Expr(ctx, tD->getLhs()) / toZ3Expr(ctx, tD->getRhs());
  } else if (t->isConstantInt32()) {
    auto tC = static_cast<const ConstantInt32*>(t);
    return ctx->bv_val(tC->getValue(), 32);
  } else {
    cout << "Error unsupported term " << t->toString() << endl;
    throw;
  }
}

z3::expr Z3Solver::toZ3Expr(z3::context* ctx, const Constraint* c) {
  if (c->isTrue()) {
    return ctx->bool_val(true);
  } else if (c->isFalse()) {
    return ctx->bool_val(false);
  } else if (c->isEq()) {
    const Eq* cEq = static_cast<const Eq*>(c);
    return toZ3Expr(ctx, cEq->getLhs()) == toZ3Expr(ctx, cEq->getRhs());
  } else if (c->isNEq()) {
    auto cNEq = static_cast<const NEq*>(c);
    return toZ3Expr(ctx, cNEq->getLhs()) == toZ3Expr(ctx, cNEq->getRhs());
  } else {
    throw;
  }
}

z3::expr Z3Solver::andConstraints(z3::context* ctx, const vector<Constraint*>* state) {
  z3::expr stateExpr = ctx->bool_val(true);
  for (auto st : *state) {
    stateExpr = stateExpr && toZ3Expr(ctx, st);
  }
  return stateExpr;
}

bool Z3Solver::checkSAT(z3::solver s) {
  switch (s.check()) {
  case(z3::unsat):
    return false;
  case(z3::sat):
    return true;
  default:
    throw;
  }
}

bool Z3Solver::constraintsImply(vector<Constraint*>* state, Constraint* c) {
  z3::context ctx;
  z3::expr stateExpr = andConstraints(&ctx, state);
  z3::expr conclusion = toZ3Expr(&ctx, c);
  stateExpr = implies(stateExpr, conclusion);
  z3::solver s(ctx);
  s.add(!stateExpr);
  return !checkSAT(s);
}

bool Z3Solver::constraintsAllow(vector<Constraint*>* state, Constraint* c) {
  z3::context ctx;
  z3::expr stateExpr = andConstraints(&ctx, state);
  z3::expr conclusion = toZ3Expr(&ctx, c);
  stateExpr = stateExpr && conclusion;
  z3::solver s(ctx);
  s.add(stateExpr);
  return checkSAT(s);
}
