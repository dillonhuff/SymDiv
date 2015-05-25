#include "SymbolicExecution/Constraint/Eq.h"
#include "SymbolicExecution/Constraint/Minus.h"
#include "SymbolicExecution/Constraint/Plus.h"
#include "SymbolicExecution/Constraint/Symbol.h"
#include "SymbolicExecution/Constraint/Term.h"
#include "SymbolicExecution/Constraint/Times.h"
#include "SymbolicExecution/Constraint/True.h"
#include "SymbolicExecution/Engine.h"
#include "SymbolicExecution/EngineTests.h"
#include "SymbolicExecution/TestUtils.h"
#include "SymbolicExecution/Z3Solver.h"

#include <iostream>

using namespace std;

void initializeEngine() {
  Z3Solver solver;
  Engine e(&solver);
  auto s = e.addSymbol(INT_32);
  auto actual = e.getConstraint(s);
  True expected;
  test(&expected, actual);
}

void execAdd() {
  Z3Solver solver;
  Engine e(&solver);
  auto lhs = e.addSymbol(INT_32);
  auto rhs = e.addSymbol(INT_32);
  auto res = e.executeBinop(ADD, lhs, rhs);
  auto add = Plus(e.getValueSym(lhs), e.getValueSym(rhs));
  Eq expected(e.getValueSym(res), &add);
  auto actual = e.getConstraint(res);
  test(&expected, actual);
}

void execSub() {
  Z3Solver solver;
  Engine e(&solver);
  auto lhs = e.addSymbol(INT_32);
  auto rhs = e.addSymbol(INT_32);
  auto res = e.executeBinop(SUB, lhs, rhs);
  auto sub = static_cast<Term>(Minus(e.getValueSym(lhs), e.getValueSym(rhs)));
  Eq expected(e.getValueSym(res), &sub);
  auto actual = e.getConstraint(res);
  test(&expected, actual);
}

void execMul() {
  Z3Solver solver;
  Engine e(&solver);
  auto lhs = e.addSymbol(INT_32);
  auto rhs = e.addSymbol(INT_32);
  auto res = e.executeBinop(MUL, lhs, rhs);
  auto times = static_cast<Term>(Times(e.getValueSym(lhs), e.getValueSym(rhs)));
  Eq expected(e.getValueSym(res), &times);
  auto actual = e.getConstraint(res);
  test(&expected, actual);
}

void execMemops() {
  Z3Solver solver;
  Engine e(&solver);
  auto a = e.addSymbol(INT_32);
  auto b = e.allocateStack(INT_32);
  e.executeStore(a, b);
  auto c = e.executeLoad(b);
  auto aEqB = Eq(e.getValueSym(a), e.getValueSym(c));
  testResult(e.stateImplies(&aEqB), "Loading store result");
}

void runEngineTests() {
  cout << "--------------------- Starting Engine Tests ---------------------" << endl;
  initializeEngine();
  execAdd();
  execSub();
  execMul();
//  execMemops();
  cout << "-----------------------------------------------------------------" << endl;
}
