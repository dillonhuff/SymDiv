#include "SymbolicExecution/Constraint/False.h"
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
  testResult(s.implies(st, &t), "true implies true");
}

void trueImpliesFalse() {
  True t;
  vector<Constraint*> st;
  st.push_back(&t);
  False f;
  Z3Solver s;
  testResult(!s.implies(st, &f), "true implies true");
}

void runZ3SolverTests() {
    cout << "--------------------- Z3 Solver Tests ---------------------" << endl;
    trueTest();
    trueImpliesFalse();
    cout << "-----------------------------------------------------------" << endl;
}
