#include "SymbolicExecution/Constraint/Eq.h"
#include "SymbolicExecution/Constraint/Minus.h"
#include "SymbolicExecution/Constraint/Plus.h"
#include "SymbolicExecution/Constraint/Symbol.h"
#include "SymbolicExecution/Constraint/Term.h"
#include "SymbolicExecution/Constraint/True.h"
#include "SymbolicExecution/Engine.h"
#include "SymbolicExecution/EngineTests.h"

#include <iostream>

using namespace std;

void test(const Constraint& expected, const Constraint& actual) {
  if (expected == actual) {
    cout << "Test passed" << endl;
  } else {
    cout << "Test FAILED" << endl;
  }
}

void initializeEngine() {
  Engine e;
  auto s = e.addSymbol(INT_32);
  auto actual = e.getConstraint(s);
  True expected;
  test(expected, actual);
}

void execAdd() {
  Engine e;
  auto lhs = e.addSymbol(INT_32);
  auto rhs = e.addSymbol(INT_32);
  auto res = e.executeBinop(ADD, lhs, rhs);
  Constraint expected(Eq(res, Plus(lhs, rhs)));
  auto actual = e.getConstraint(res);
  test(expected, actual);
}

void execSub() {
  Engine e;
  auto lhs = e.addSymbol(INT_32);
  auto rhs = e.addSymbol(INT_32);
  auto res = e.executeBinop(SUB, lhs, rhs);
  Constraint expected(Eq(res, Minus(lhs, rhs)));
  auto actual = e.getConstraint(res);
  test(expected, actual);
}

void runEngineTests() {
  cout << "--------------------- Starting Engine Tests ---------------------" << endl;
  initializeEngine();
  execAdd();
  execSub();
  cout << "-----------------------------------------------------------------" << endl;
}
