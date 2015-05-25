#include "SymbolicExecution/Constraint/ConstantInt32.h"

bool ConstantInt32::operator==(const Term* other) const {
  if (other->isConstantInt32()) {
    auto otherConst = static_cast<const ConstantInt32*>(other);
    return getValue() == otherConst->getValue();
  }
  return false;
}
