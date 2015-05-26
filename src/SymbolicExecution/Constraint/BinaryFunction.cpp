#include "SymbolicExecution/Constraint/BinaryFunction.h"

bool BinaryFunction::operator==(const Term* other) const {
  if (other->isBinaryFunction() && Term::operator==(other)) {
    auto otherBFunc = static_cast<const BinaryFunction*>(other);
    return *rhs == otherBFunc->rhs && *lhs == otherBFunc->lhs;
  }
  return false;
}

std::string BinaryFunction::toString() const {
  std::string res = "(";
  res += termKindToString(kind) + " ";
  res += lhs->toString() + " ";
  res += rhs->toString();
  res += ")";
  return res;
}

