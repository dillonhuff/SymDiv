#include "SymbolicExecution/Constraint/Eq.h"
#include "SymbolicExecution/Constraint/False.h"
#include "SymbolicExecution/Constraint/Plus.h"
#include "SymbolicExecution/Constraint/Symbol.h"
#include "SymbolicExecution/Constraint/True.h"
#include "SymbolicExecution/TestUtils.h"
#include "SymbolicExecution/Z3Solver.h"
#include "SymbolicExecution/Z3SolverTests.h"

#include <iostream>
#include <vector>

using namespace std;

void trueTest() {
  True t;
  vector<Constraint*> st;
  st.push_back(&t);
  Z3Solver s;
  testResult(s.constraintsImply(&st, &t), "true implies true");
}

void trueImpliesFalse() {
  True t;
  vector<Constraint*> st;
  st.push_back(&t);
  False f;
  Z3Solver s;
  testResult(!s.constraintsImply(&st, &f), "true implies true");
}

void aEqualsA() {
  Symbol a(INT_32, 0);
  Eq aEqA(&a, &a);
  vector<Constraint*> st;
  Z3Solver s;
  testResult(s.constraintsImply(&st, &aEqA), "a == a");
}

void transitiveAdd() {
  Symbol a(INT_32, 0);
  Symbol b(INT_32, 1);
  Symbol c(INT_32, 2);
  Symbol d(INT_32, 3);
  Symbol e(INT_32, 4);
  Symbol f(INT_32, 5);

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
  testResult(s.constraintsImply(&st, &e3), "a + b = c + d ^ c + d = e + f -> a + b = e + f");
}

void runZ3SolverTests() {
  cout << "--------------------- Z3 Solver Tests ---------------------" << endl;
  trueTest();
  trueImpliesFalse();
  aEqualsA();
  transitiveAdd();
  cout << "-----------------------------------------------------------" << endl;
}
