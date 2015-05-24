#include "SymbolicExecution/TestUtils.h"

#include <iostream>

using namespace std;

void test(const Constraint* expected, const Constraint* actual) {
  if (*expected == actual) {
    cout << "Test passed" << endl;
  } else {
    cout << "Test FAILED" << endl;
  }
}

void testNEQ(const Constraint* expected, const Constraint* actual) {
  if (*expected == actual) {
    cout << "Test FAILED" << endl;
  } else {
    cout << "Test passed" << endl;
  }
}

