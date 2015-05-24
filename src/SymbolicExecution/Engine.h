#ifndef ENGINE_H
#define ENGINE_H

#include "SymbolicExecution/Constraint/Constraint.h"
#include "SymbolicExecution/Constraint/Symbol.h"
#include "SymbolicExecution/Constraint/Term.h"

#include <map>
#include <vector>
#include <utility>

using namespace std;
class Engine {
protected:
map<Symbol, pair<Symbol*, Constraint*>> symbolicMemory;
vector<Constraint*> allConstraints;
vector<Term*> allTerms;
int nextSymId;

Constraint* mkTrue();
Constraint* mkEq(const Term* lhs, const Term* rhs);
Term* mkPlus(const Term* lhs, const Term* rhs);
Symbol* mkSymbol(SymbolType t);

 public:
Engine();
~Engine();
  const Symbol& addSymbol(SymbolType t);
  const Constraint& getConstraint(Symbol& s) const;
  const Symbol* getValueSym(Symbol& s) const;
  const Symbol& executeBinop(OpCode c, const Symbol* lhs, const Symbol* rhs);
};

#endif
