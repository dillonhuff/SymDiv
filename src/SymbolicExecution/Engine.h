#ifndef ENGINE_H
#define ENGINE_H

#include "SymbolicExecution/Constraint/Constraint.h"
#include "SymbolicExecution/Constraint/Symbol.h"
#include "SymbolicExecution/Constraint/Term.h"
#include "SymbolicExecution/ConstraintSolver.h"

#include <map>
#include <vector>
#include <utility>

using namespace std;

class Engine {
 protected:
  ConstraintSolver* solver;
  map<const Symbol*, pair<Symbol*, Constraint*>> symbolicMemory;
  vector<Constraint*> allConstraints;
  vector<Term*> allTerms;
  int nextSymId;

  Constraint* mkTrue();
  Constraint* mkEq(const Term* lhs, const Term* rhs);
  Term* mkPlus(const Term* lhs, const Term* rhs);
  Term* mkMinus(const Term* lhs, const Term* rhs);
  Term* mkTimes(const Term* lhs, const Term* rhs);
  Symbol* mkSymbol(SymbolType t);

  const Symbol* executeAdd(const Symbol* lhs, const Symbol* rhs);
  const Symbol* executeSub(const Symbol* lhs, const Symbol* rhs);
  const Symbol* executeMul(const Symbol* lhs, const Symbol* rhs);

 public:
  Engine(ConstraintSolver* s);

  const Symbol* addSymbol(SymbolType t);
  const Constraint* getConstraint(const Symbol* s) const;
  const Symbol* getValueSym(const Symbol* s) const;
  const Symbol* executeBinop(OpCode c, const Symbol* lhs, const Symbol* rhs);
  const Symbol* allocateStack(SymbolType t) { return nullptr; }
  void executeStore(const Symbol* val, const Symbol* location) { return; }
  const Symbol* executeLoad(const Symbol* location) { return nullptr; }

  bool stateImplies(Constraint* c);
};

#endif
