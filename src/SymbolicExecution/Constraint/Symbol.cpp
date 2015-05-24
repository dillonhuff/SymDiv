#include "SymbolicExecution/Constraint/Symbol.h"

bool Symbol::operator==(const Term* other) const {
  if (other->isSymbol()) {
    auto otherSym = static_cast<const Symbol*>(other);
    return id == otherSym->id;
  }
  return false;
}
