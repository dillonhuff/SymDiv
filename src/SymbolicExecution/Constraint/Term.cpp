#include "SymbolicExecution/Constraint/Term.h"

#include <iostream>

using namespace std;

bool Term::operator==(const Term& other) const {
  return kind == other.kind;
}

bool Term::operator==(const Term* other) const {
  return kind == other->kind;
}
