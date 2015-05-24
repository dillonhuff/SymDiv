#include "SymbolicExecution/Constraint/Eq.h"
#include "SymbolicExecution/Constraint/Minus.h"
#include "SymbolicExecution/Constraint/Plus.h"
#include "SymbolicExecution/Constraint/Symbol.h"
#include "SymbolicExecution/Constraint/Term.h"
#include "SymbolicExecution/Constraint/True.h"
#include "SymbolicExecution/Engine.h"
#include "SymbolicExecution/EngineTests.h"
#include "SymbolicExecution/TestUtils.h"

#include <iostream>

using namespace std;

void initializeEngine() {
  Engine e;
  auto s = e.addSymbol(INT_32);
  auto actual = e.getConstraint(s);
  True expected;
  test(&expected, actual);
}

void execAdd() {
  Engine e;
  auto lhs = e.addSymbol(INT_32);
  auto rhs = e.addSymbol(INT_32);
  auto res = e.executeBinop(ADD, lhs, rhs);
  auto add = Plus(e.getValueSym(lhs), e.getValueSym(rhs));
  Eq expected(e.getValueSym(res), &add);
  auto actual = e.getConstraint(res);
  //  cout << "Expected " << expected.toString() << endl;
  //  cout << "Actual " << actual->toString() << endl;
  test(&expected, actual);
}

void execSub() {
  Engine e;
  auto lhs = e.addSymbol(INT_32);
  auto rhs = e.addSymbol(INT_32);
  auto res = e.executeBinop(SUB, lhs, rhs);
  auto sub = static_cast<Term>(Minus(e.getValueSym(lhs), e.getValueSym(rhs)));
  Eq expected(e.getValueSym(res), &sub);
  auto actual = e.getConstraint(res);
  test(&expected, actual);
}

void runEngineTests() {
  cout << "--------------------- Starting Engine Tests ---------------------" << endl;
  initializeEngine();
  execAdd();
  execSub();
  cout << "-----------------------------------------------------------------" << endl;
}
