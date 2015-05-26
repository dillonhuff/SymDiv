#ifndef ENGINE_H
#define ENGINE_H

#include "SymbolicExecution/Constraint/Constraint.h"
#include "SymbolicExecution/Constraint/Eq.h"
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
  map<const Symbol*, pair<const Symbol*, Constraint*>> symbolicMemory;
  vector<Constraint*> allConstraints;
  vector<Term*> allTerms;
  int nextSymId;

  Constraint* mkTrue();
  Constraint* mkEq(const Term* lhs, const Term* rhs);
  Term* mkPlus(const Term* lhs, const Term* rhs);
  Term* mkMinus(const Term* lhs, const Term* rhs);
  Term* mkTimes(const Term* lhs, const Term* rhs);
  Term* mkConstantInt32(int val);
  Symbol* mkSymbol(SymbolType t);

  const Term* extractAddrFromEq(const Eq* eq, const Symbol* ptr);
  const Symbol* extractAddrPointedToBy(const Eq* eq, const Symbol* ptr);
  const Symbol* addrPointedToBy(const Symbol* ptr);

  void setConstraint(const Symbol* s, Constraint* c);

  const Symbol* executeAdd(const Symbol* lhs, const Symbol* rhs);
  const Symbol* executeSub(const Symbol* lhs, const Symbol* rhs);
  const Symbol* executeMul(const Symbol* lhs, const Symbol* rhs);

  void getConstraintState(vector<Constraint*>* constraintState);

 public:
  Engine(ConstraintSolver* s);

  const Symbol* addSymbol(SymbolType t);
  const Symbol* addConstantInt32(int val);
  const Constraint* getConstraint(const Symbol* s) const;
  const Symbol* getValueSym(const Symbol* s) const;
  const Symbol* executeBinop(OpCode c, const Symbol* lhs, const Symbol* rhs);
  const Symbol* allocateStack(SymbolType t);
  void executeStore(const Symbol* val, const Symbol* locationPtr);
  const Symbol* executeLoad(const Symbol* locationPtr);

  bool stateImplies(Constraint* c);
  bool stateAllows(Constraint* c);
};

#endif
