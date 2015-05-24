#ifndef ENGINE_H
#define ENGINE_H

#include "SymbolicExecution/Constraint/Constraint.h"
#include "SymbolicExecution/Constraint/Symbol.h"
#include "SymbolicExecution/Constraint/Term.h"

class Engine {
 public:
  const Symbol& addSymbol(SymbolType t);
  const Constraint& getConstraint(Symbol& s) const;
  const Symbol& executeBinop(OpCode c, const Symbol& lhs, const Symbol& rhs);
};

#endif
