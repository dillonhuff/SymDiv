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
