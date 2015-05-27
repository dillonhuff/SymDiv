#include "SymbolicExecution/Constraint/ConstantInt32.h"
#include "SymbolicExecution/Constraint/Divide.h"
#include "SymbolicExecution/Constraint/Eq.h"
#include "SymbolicExecution/Constraint/False.h"
#include "SymbolicExecution/Constraint/Minus.h"
#include "SymbolicExecution/Constraint/NEq.h"
#include "SymbolicExecution/Constraint/Plus.h"
#include "SymbolicExecution/Constraint/Symbol.h"
#include "SymbolicExecution/Constraint/True.h"
#include "SymbolicExecution/ConstraintTests.h"
#include "SymbolicExecution/ExpressionFactory.h"
#include "SymbolicExecution/TestUtils.h"
#include "SymbolicExecution/Type/TypeSystem.h"

#include <iostream>

using namespace std;

void trueEqualsTrue(ExpressionFactory* f) {
  True c1;
  True c2;

  test(&c1, &c2);
}

void falseEqualsFalse(ExpressionFactory* f) {
  False c1;
  False c2;

  test(&c1, &c2);
}

void falseNEQTrue(ExpressionFactory* f) {
  False c1;
  True c2;
  testNEQ(&c1, &c2);
}

void equalSymsEqual(ExpressionFactory* f) {
  Symbol s1(f->mkInt(32), 0);
  Symbol s2(f->mkInt(32), 1);

  Eq eq1(&s1, &s2);
  Eq eq2(&s1, &s2);

  test(&eq1, &eq2);
}

void sameSymsEqual(ExpressionFactory* f) {
  Symbol s1(f->mkInt(32), 0);
  Symbol s2(f->mkInt(32), 1);
  Eq eq1(&s1, &s2);

  Symbol s3(f->mkInt(32), 0);
  Symbol s4(f->mkInt(32), 1);
  Eq eq2(&s3, &s4);

  test(&eq1, &eq2);
}

void eqsWithDifferentArgsNotEqual(ExpressionFactory* f) {
  Symbol s1(f->mkInt(32), 0);
  Symbol s2(f->mkInt(32), 1);
  Eq eq1(&s1, &s2);

  Symbol s3(f->mkInt(32), 2);
  Symbol s4(f->mkInt(32), 3);
  Eq eq2(&s3, &s4);

  testNEQ(&eq1, &eq2);
}

void eqPlusAndEqMinusNotEqual_1(ExpressionFactory* f) {
  Symbol s1(f->mkInt(32), 0);
  Symbol s2(f->mkInt(32), 1);
  Symbol s3(f->mkInt(32), 2);

  Plus plus(&s1, &s2);
  Eq plusEq(&s3, &plus);

  Symbol s4(f->mkInt(32), 0);
  Symbol s5(f->mkInt(32), 1);
  Symbol s6(f->mkInt(32), 2);
  
  Minus minus(&s4, &s5);
  Eq minusEq(&s6, &minus);

  testNEQ(&plusEq, &minusEq);
}

void eqPlusAndEqMinusNotEqual_2(ExpressionFactory* f) {
  Symbol s1(f->mkInt(32), 0);
  Symbol s2(f->mkInt(32), 1);
  Symbol s3(f->mkInt(32), 2);

  Plus plus(&s1, &s2);
  Eq plusEq(&s3, &plus);
  
  Minus minus(&s1, &s2);
  Eq minusEq(&s3, &minus);

  testNEQ(&plusEq, &minusEq);
}

void identicalEqsEqual(ExpressionFactory* f) {
  Symbol s1(f->mkInt(32), 0);
  Symbol s2(f->mkInt(32), 1);
  Symbol s3(f->mkInt(32), 2);
  Plus plus1(&s1, &s2);
  Eq eq1(&s3, &plus1);

  Symbol s4(f->mkInt(32), 0);
  Symbol s5(f->mkInt(32), 1);
  Symbol s6(f->mkInt(32), 2);
  Plus plus2(&s4, &s5);
  Eq eq2(&s6, &plus2);

  test(&eq1, &eq2);
}

void constantsEqual(ExpressionFactory* f) {
  ConstantInt32 c1(123);
  ConstantInt32 c2(123);

  Eq e1(&c1, &c2);
  Eq e2(&c1, &c2);

  test(&e1, &e2);
}

void differentConstantsNotEqual(ExpressionFactory* f) {
  ConstantInt32 c1(12);
  ConstantInt32 c2(-9);

  Eq e1(&c1, &c1);
  Eq e2(&c2, &c1);

  testNEQ(&e1, &e2);
}

void differentConstantsNEQ(ExpressionFactory* f) {
  ConstantInt32 c1(3);
  ConstantInt32 c2(-23);

  NEq neq(&c1, &c2);

  test(&neq, &neq);
}

void eqAndNEqDifferent(ExpressionFactory* f) {
  ConstantInt32 c1(3);
  ConstantInt32 c2(-23);

  NEq neq(&c1, &c2);
  Eq eq(&c1, &c2);

  testNEQ(&neq, &eq);
}

void neqDivide(ExpressionFactory* f) {
  Symbol s1(f->mkInt(32), 0);
  Symbol s2(f->mkInt(32), 1);

  ConstantInt32 c1(3);

  Divide d1(&s1, &c1);

  NEq neq1(&s1, &d1);
  NEq neq2(&s2, &d1);

  testNEQ(&neq1, &neq2);
}

void runConstraintTests() {
  cout << "--------------------- Starting Constraint Tests -----------------" << endl;
  ExpressionFactory f;
  trueEqualsTrue(&f);
  falseEqualsFalse(&f);
  falseNEQTrue(&f);
  sameSymsEqual(&f);
  equalSymsEqual(&f);
  eqsWithDifferentArgsNotEqual(&f);
  eqPlusAndEqMinusNotEqual_1(&f);
  eqPlusAndEqMinusNotEqual_2(&f);
  identicalEqsEqual(&f);
  constantsEqual(&f);
  differentConstantsNotEqual(&f);
  differentConstantsNEQ(&f);
  eqAndNEqDifferent(&f);
  neqDivide(&f);
  cout << "-----------------------------------------------------------------" << endl << endl;
}
