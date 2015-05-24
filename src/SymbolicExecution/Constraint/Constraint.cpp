#include "SymbolicExecution/Constraint/Constraint.h"

std::string constraintKindToString(ConstraintKind k) {
  switch(k) {
  case(EQ):
    return "==";
  case(TRUE):
    return "T";
  case(FALSE):
    return "F";
  default:
    return "ERROR UNSUPPORTED CONSTRAINT KIND";
  }
}

bool Constraint::operator==(const Constraint& other) const{
  return getKind() == other.getKind();
}

bool Constraint::operator==(const Constraint* other) const{
  return getKind() == other->getKind();
}

ConstraintKind Constraint::getKind() const {
  return kind;
}
