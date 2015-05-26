#ifndef ENGINE_H
#define ENGINE_H

#include "SymbolicExecution/Constraint/Constraint.h"
#include "SymbolicExecution/Constraint/Eq.h"
#include "SymbolicExecution/Constraint/Symbol.h"
#include "SymbolicExecution/Constraint/Term.h"
#include "SymbolicExecution/ConstraintSolver.h"
#include "SymbolicExecution/ExpressionFactory.h"
#include "SymbolicExecution/OperationResult.h"

#include <map>
#include <vector>
#include <utility>

using namespace std;

class Engine {
 protected:
  ConstraintSolver* solver;
  ExpressionFactory* f;
  map<const Symbol*, pair<const Symbol*, Constraint*>> symbolicMemory;

  const Term* extractAddrFromEq(const Eq* eq, const Symbol* ptr);
  const Symbol* extractAddrPointedToBy(const Eq* eq, const Symbol* ptr);
  const Symbol* addrPointedToBy(const Symbol* ptr);

  void setConstraint(const Symbol* s, Constraint* c);

  const Symbol* executeAdd(const Symbol* lhs, const Symbol* rhs);
  const Symbol* executeSub(const Symbol* lhs, const Symbol* rhs);
  const Symbol* executeMul(const Symbol* lhs, const Symbol* rhs);

  void getConstraintState(vector<Constraint*>* constraintState);

 public:
  Engine(ConstraintSolver* s, ExpressionFactory* factory);

  const Symbol* addSymbol(SymbolType t);
  const Symbol* addConstantInt32(int val);
  const Constraint* getConstraint(const Symbol* s) const;
  const Symbol* getValueSym(const Symbol* s) const;
  const Symbol* executeBinop(OpCode c, const Symbol* lhs, const Symbol* rhs);
  OperationResult executeDiv(const Symbol* lhs, const Symbol* rhs);
  const Symbol* allocateStack(SymbolType t);
  void executeStore(const Symbol* val, const Symbol* locationPtr);
  const Symbol* executeLoad(const Symbol* locationPtr);

  bool stateImplies(Constraint* c);
  bool stateAllows(Constraint* c);

  std::string toString() const;
};

#endif
