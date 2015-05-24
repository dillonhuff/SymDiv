#include "BinaryPredicate.h"

bool BinaryPredicate::operator==(const Constraint& other) const {
  if (other.isBinaryPredicate() && Constraint::operator==(other)) {
    auto otherPred = static_cast<const BinaryPredicate&>(other);
    return rhs == otherPred.rhs && lhs == otherPred.lhs;
  }
  return false;
}

