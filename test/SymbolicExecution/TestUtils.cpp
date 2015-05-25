#include "SymbolicExecution/TestUtils.h"

using namespace std;

void testResult(bool res, string testName) {
  cout << testName;
  if (res) {
    cout << " passed" << endl;
  } else {
    cout << " FAILED" << endl;
  }
}

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

