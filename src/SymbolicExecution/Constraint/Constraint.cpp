#include "SymbolicExecution/Constraint/Constraint.h"

#include <iostream>

using namespace std;

bool Constraint::operator==(const Constraint& other) const{
  cout << "constraint operator ==" << endl;
  return getKind() == other.getKind();
}

ConstraintKind Constraint::getKind() const {
  return kind;
}
