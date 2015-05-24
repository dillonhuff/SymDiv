#include "BinaryPredicate.h"

#include <iostream>

using namespace std;

bool BinaryPredicate::operator==(const Constraint& other) const {
  if (other.isBinaryPredicate() && Constraint::operator==(other)) {
    auto otherPred = static_cast<const BinaryPredicate&>(other);
    bool lhsRes = *lhs == otherPred.lhs;
    auto otherRhs = otherPred.rhs;
    bool rhsRes =  *rhs == otherRhs;
    return lhsRes && rhsRes;
  }
  return false;
}

