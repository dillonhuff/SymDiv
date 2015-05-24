#include "SymbolicExecution/Constraint/Constraint.h"

bool Constraint::operator==(const Constraint& other) const{
  return getKind() == other.getKind();
}

ConstraintKind Constraint::getKind() const {
  return kind;
}
