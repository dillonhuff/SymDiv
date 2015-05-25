#include "SymbolicExecution/ConstraintTests.h"
#include "SymbolicExecution/EngineTests.h"
#include "SymbolicExecution/Z3SolverTests.h"

#include <iostream>

using namespace std;

int main() {
  runEngineTests();
  runConstraintTests();
  runZ3SolverTests();
}
