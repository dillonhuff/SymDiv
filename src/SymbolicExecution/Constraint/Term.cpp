#include "SymbolicExecution/Constraint/Term.h"

#include <iostream>

using namespace std;

bool Term::operator==(const Term& other) const {
  cout << "Term eq" << endl;
  return kind == other.kind;
}

bool Term::operator==(const Term* other) const {
  cout << "Term eq" << endl;
  return kind == other->kind;
}
