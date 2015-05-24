#include "SymbolicExecution/Engine.h"

const Symbol& Engine::addSymbol(SymbolType t) {
  Symbol s;
  return s;
}

const Constraint& Engine::getConstraint(Symbol& s) const {
  Constraint c;
  return c;
}

const Symbol& Engine::executeBinop(OpCode c, const Symbol& lhs, const Symbol& rhs) {
  return lhs;
}
