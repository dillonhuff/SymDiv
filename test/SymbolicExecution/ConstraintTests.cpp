#include "SymbolicExecution/Constraint/Eq.h"
#include "SymbolicExecution/Constraint/False.h"
#include "SymbolicExecution/Constraint/Minus.h"
#include "SymbolicExecution/Constraint/Plus.h"
#include "SymbolicExecution/Constraint/Symbol.h"
#include "SymbolicExecution/Constraint/True.h"
#include "SymbolicExecution/ConstraintTests.h"
#include "SymbolicExecution/TestUtils.h"

#include <iostream>

using namespace std;

void trueEqualsTrue() {
  True c1;
  True c2;

  test(c1, c2);
}

void falseEqualsFalse() {
  False c1;
  False c2;

  test(c1, c2);
}

void falseNEQTrue() {
  False c1;
  True c2;
  testNEQ(c1, c2);
}

void eqSymsEqualsItself() {
  Symbol s1(INT_32, 0);
  Symbol s2(INT_32, 1);

  Eq eq1(&s1, &s2);
  Eq eq2(&s1, &s2);

  test(eq1, eq2);
}

void eqsWithDifferentArgsNotEqual() {
  Symbol s1(INT_32, 0);
  Symbol s2(INT_32, 1);
  Eq eq1(&s1, &s2);

  Symbol s3(INT_32, 2);
  Symbol s4(INT_32, 3);
  Eq eq2(&s3, &s4);

  testNEQ(eq1, eq2);
}

void eqPlusAndEqMinusNotEqual() {
  Symbol s1(INT_32, 0);
  Symbol s2(INT_32, 1);
  Symbol s3(INT_32, 2);

  Plus plus(&s1, &s2);
  Eq plusEq(&s3, &plus);
  
  Minus minus(&s1, &s2);
  Eq minusEq(&s3, &minus);

  testNEQ(plusEq, minusEq);
}

void runConstraintTests() {
  cout << "--------------------- Starting Constraint Tests -----------------" << endl;
  trueEqualsTrue();
  falseEqualsFalse();
  falseNEQTrue();
  eqSymsEqualsItself();
  eqsWithDifferentArgsNotEqual();
  eqPlusAndEqMinusNotEqual();
  cout << "-----------------------------------------------------------------" << endl << endl;
}
