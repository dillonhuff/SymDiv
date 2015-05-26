#include "SymbolicExecution/Constraint/ConstantInt32.h"
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
  auto aEqC = Eq(e.getValueSym(a), e.getValueSym(c));
  testResult(e.stateImplies(&aEqC), "Loading store result");
}

void twoDifferentStoresNotEqual() {
  Z3Solver solver;
  Engine e(&solver);
  auto a = e.addSymbol(INT_32);
  auto b = e.addSymbol(INT_32);
  auto c = e.allocateStack(INT_32);
  auto d = e.allocateStack(INT_32);
  e.executeStore(a, c);
  e.executeStore(b, d);
  auto aL = e.executeLoad(c);
  auto bL = e.executeLoad(d);
  auto blEqAl = Eq(e.getValueSym(aL), e.getValueSym(bL));
  testResult(!e.stateImplies(&blEqAl), "Two different loads are not equal");
}

void loadStoreConstant() {
  Z3Solver solver;
  Engine e(&solver);
  auto a = e.addConstantInt32(12);
  auto b = e.allocateStack(INT_32);
  e.executeStore(a, b);
  auto c = e.executeLoad(b);
  ConstantInt32 d(12);
  auto cEqd = Eq(e.getValueSym(c), &d);
  testResult(e.stateImplies(&cEqd), "Store load operation on integer constant");
}

void storeDoesntChangePtr() {
  Z3Solver solver;
  Engine e(&solver);
  auto a = e.addConstantInt32(12);
  auto b = e.allocateStack(INT_32);
  e.executeStore(a, b);
  e.executeLoad(b);
  auto aEqB = Eq(e.getValueSym(a), e.getValueSym(b));
  testResult(!e.stateImplies(&aEqB), "Store load operation doesn't change ptr value");
}

void oneVarCouldBeZero() {
  Z3Solver solver;
  Engine e(&solver);
  auto a = e.addSymbol(INT_32);
  ConstantInt32 zero(0);
  Eq aEqZero(e.getValueSym(a), &zero);
  testResult(e.stateAllows(&aEqZero), "Just initialized symbol could be zero");
}

void nonZeroConstantCannotBeZero() {
  Z3Solver solver;
  Engine e(&solver);
  auto a = e.addConstantInt32(12);
  ConstantInt32 zero(0);
  Eq aEqZero(e.getValueSym(a), &zero);
  testResult(!e.stateAllows(&aEqZero), "Nonzero constant cannot be zero");
}

void runEngineTests() {
  cout << "--------------------- Starting Engine Tests ---------------------" << endl;
  initializeEngine();
  execAdd();
  execSub();
  execMul();
  execMemops();
  twoDifferentStoresNotEqual();
  loadStoreConstant();
  storeDoesntChangePtr();
  oneVarCouldBeZero();  
  nonZeroConstantCannotBeZero();
  cout << "-----------------------------------------------------------------" << endl << endl;
}
