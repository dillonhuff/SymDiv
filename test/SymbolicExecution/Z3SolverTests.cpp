#include "SymbolicExecution/Constraint/ConstantInt32.h"
#include "SymbolicExecution/Constraint/Divide.h"
#include "SymbolicExecution/Constraint/Eq.h"
#include "SymbolicExecution/Constraint/False.h"
#include "SymbolicExecution/Constraint/Minus.h"
#include "SymbolicExecution/Constraint/NEq.h"
#include "SymbolicExecution/Constraint/Plus.h"
#include "SymbolicExecution/Constraint/Symbol.h"
#include "SymbolicExecution/Constraint/Times.h"
#include "SymbolicExecution/Constraint/True.h"
#include "SymbolicExecution/ExpressionFactory.h"
#include "SymbolicExecution/TestUtils.h"
#include "SymbolicExecution/Type/TypeSystem.h"
#include "SymbolicExecution/Z3Solver.h"
#include "SymbolicExecution/Z3SolverTests.h"

#include <iostream>
#include <vector>

using namespace std;

void trueTest(ExpressionFactory* fac) {
  True t;
  vector<Constraint*> st;
  st.push_back(&t);
  Z3Solver s;
  testResult(s.constraintsImply(&st, &t), "true implies true");
}

void trueImpliesFalse(ExpressionFactory* fac) {
  True t;
  vector<Constraint*> st;
  st.push_back(&t);
  False f;
  Z3Solver s;
  testResult(!s.constraintsImply(&st, &f), "true does not imply false");
}

void aEqualsA(ExpressionFactory* fac) {
  Symbol a(fac->mkInt(32), 0);
  Eq aEqA(&a, &a);
  vector<Constraint*> st;
  Z3Solver s;
  testResult(s.constraintsImply(&st, &aEqA), "a == a");
}

void transitiveAdd(ExpressionFactory* fac) {
  Symbol a(fac->mkInt(32), 0);
  Symbol b(fac->mkInt(32), 1);
  Symbol c(fac->mkInt(32), 2);
  Symbol d(fac->mkInt(32), 3);
  Symbol e(fac->mkInt(32), 4);
  Symbol f(fac->mkInt(32), 5);

  Plus aPlusb(&a, &b);
  Plus cPlusd(&c, &d);
  Plus ePlusf(&e, &f);

  Eq e1(&aPlusb, &cPlusd);
  Eq e2(&cPlusd, &ePlusf);
  Eq e3(&aPlusb, &ePlusf);

  vector<Constraint*> st;
  st.push_back(&e1);
  st.push_back(&e2);

  Z3Solver s;
  testResult(s.constraintsImply(&st, &e3), "a + b == c + d ^ c + d == e + f -> a + b == e + f");
}

void twoConstantsEq(ExpressionFactory* fac) {
  ConstantInt32 a(45);
  Eq eq(&a, &a);

  vector<Constraint*> st;

  Z3Solver s;
  testResult(s.constraintsImply(&st, &eq), "True -> 45 == 45");
}

void identicalDividesEq(ExpressionFactory* fac) {
  ConstantInt32 a(23);
  ConstantInt32 b(23);

  Symbol c1(fac->mkInt(32), 0);
  Symbol c2(fac->mkInt(32), 0);

  Symbol c3(fac->mkInt(32), 1);
  Symbol c4(fac->mkInt(32), 1);

  Divide d1(&c1, &a);
  Divide d2(&c2, &b);

  Eq eq1(&c3, &d1);
  Eq eq2(&c4, &d2);

  vector<Constraint*> st;
  st.push_back(&eq1);

  Z3Solver s;
  testResult(s.constraintsImply(&st, &eq2), "a == b / 23 -> a == b / 23");
}

void simpleNEq(ExpressionFactory* fac) {
  Symbol a(fac->mkInt(32), 0);
  ConstantInt32 z(0);
  
  NEq aNonZero(&a, &z);

  vector<Constraint*> st;
  st.push_back(&aNonZero);

  Z3Solver s;
  testResult(s.constraintsImply(&st, &aNonZero), "a != 0 -> a != 0");
}

void simpleMinus(ExpressionFactory* fac) {
  Symbol a(fac->mkInt(32), 0);
  ConstantInt32 zero(0);
  Minus aMinusA(&a, &a);
  Eq aMinusAIsZero(&zero, &aMinusA);

  vector<Constraint*> st;

  Z3Solver s;
  testResult(s.constraintsImply(&st, &aMinusAIsZero), "a - a == 0");
}

void simpleTimes(ExpressionFactory* fac) {
  Symbol a(fac->mkInt(32), 0);
  Symbol b(fac->mkInt(32), 1);
  Symbol c(fac->mkInt(32), 2);

  Eq bEqC(&b, &c);
  

  vector<Constraint*> st;
  st.push_back(&bEqC);

  Times aTimesB(&a, &b);
  Times cTimesA(&c, &a);
  Eq aTBEqcTA(&aTimesB, &cTimesA);

  Z3Solver s;
  testResult(s.constraintsImply(&st, &aTBEqcTA), "b == c -> a*b == c*a");
}

void runZ3SolverTests() {
  cout << "--------------------- Z3 Solver Tests ---------------------" << endl;
  ExpressionFactory f;
  trueTest(&f);
  trueImpliesFalse(&f);
  aEqualsA(&f);
  transitiveAdd(&f);
  twoConstantsEq(&f);
  identicalDividesEq(&f);
  simpleNEq(&f);
  simpleMinus(&f);
  simpleTimes(&f);
  cout << "-----------------------------------------------------------" << endl;
}
