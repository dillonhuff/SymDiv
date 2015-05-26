#include "SymbolicExecution/Constraint/ConstantInt32.h"
#include "SymbolicExecution/Constraint/Eq.h"
#include "SymbolicExecution/Constraint/Minus.h"
#include "SymbolicExecution/Constraint/Plus.h"
#include "SymbolicExecution/Constraint/Times.h"
#include "SymbolicExecution/Constraint/True.h"
#include "SymbolicExecution/Engine.h"

#include <iostream>

using namespace std;

Engine::Engine(ConstraintSolver* s) {
  nextSymId = 0;
  solver = s;
}

Constraint* Engine::mkEq(const Term* lhs, const Term* rhs) {
  auto eq = new Eq(lhs, rhs);
  allConstraints.push_back(eq);
  return eq;
}

Term* Engine::mkPlus(const Term* lhs, const Term* rhs) {
  auto plus = new Plus(lhs, rhs);
  allTerms.push_back(plus);
  return plus;
}

Term* Engine::mkMinus(const Term* lhs, const Term* rhs) {
  auto minus = new Minus(lhs, rhs);
  allTerms.push_back(minus);
  return minus;
}

Term* Engine::mkConstantInt32(int val) {
  auto constant = new ConstantInt32(val);
  allTerms.push_back(constant);
  return constant;
}

Term* Engine::mkTimes(const Term* lhs, const Term* rhs) {
  auto times = new Times(lhs, rhs);
  allTerms.push_back(times);
  return times;
}

Symbol* Engine::mkSymbol(SymbolType t) {
  auto s = new Symbol(t, nextSymId);
  nextSymId++;
  allTerms.push_back(s);
  return s;
}

Constraint* Engine::mkTrue() {
  auto t = new True();
  allConstraints.push_back(t);
  return t;
}

const Symbol* Engine::addSymbol(SymbolType t) {
  auto sVal = mkSymbol(t);
  auto sPtr = mkSymbol(PTR);
  symbolicMemory[sPtr] = pair<Symbol*, Constraint*>(sVal, mkTrue());
  return sPtr;
}

const Symbol* Engine::addConstantInt32(int val) {
  auto constVal = mkConstantInt32(val);
  auto sVal = mkSymbol(INT_32);
  auto sPtr = mkSymbol(PTR);
  symbolicMemory[sPtr] = pair<Symbol*, Constraint*>(sVal, mkEq(sVal, constVal));
  return sPtr;
}

const Constraint* Engine::getConstraint(const Symbol* s) const {
  auto m = symbolicMemory;
  auto symValConstraintPair = m[s];
  return symValConstraintPair.second;
}

const Symbol* Engine::getValueSym(const Symbol* s) const {
  auto m = symbolicMemory;
  auto symValConstraintPair = m[s];
  return symValConstraintPair.first;
}

const Symbol* Engine::executeBinop(OpCode c, const Symbol* lhs, const Symbol* rhs) {
  switch(c) {
  case(ADD):
    return executeAdd(lhs, rhs);
  case(SUB):
    return executeSub(lhs, rhs);
  case(MUL):
    return executeMul(lhs, rhs);
  default:
    cout << "Error: Bad opcode in executeBinop" << endl;
    throw;
  }
}

const Term* Engine::extractAddrFromEq(const Eq* eq, const Symbol* ptr) {
  if (eq->getRhs() == getValueSym(ptr) &&
      eq->getLhs()->isSymbol()) {
    return eq->getLhs();
  } else if (eq->getLhs() == getValueSym(ptr)
	     && eq->getRhs()->isSymbol()) {
    return eq->getRhs();
  } else {
    throw;
  }
}

const Symbol* Engine::extractAddrPointedToBy(const Eq* eq, const Symbol* ptr) {
  const Term* pointedTo = extractAddrFromEq(eq, ptr);
  auto addr = static_cast<const Symbol*>(pointedTo);
  return addr;
}

const Symbol* Engine::addrPointedToBy(const Symbol* ptr) {
  auto c = getConstraint(ptr);
  if (c->isEq()) {
    auto eq = static_cast<const Eq*>(c);
    return extractAddrPointedToBy(eq, ptr);
  } else {
    throw;
  }
}

void Engine::setConstraint(const Symbol* s, Constraint* c) {
  auto sVal = getValueSym(s);
  symbolicMemory[s] = pair<const Symbol*, Constraint*>(sVal, c);
  return;
}

const Symbol* Engine::executeAdd(const Symbol* lhs, const Symbol* rhs) {
  auto resVal = mkSymbol(INT_32);
  auto resPtr = mkSymbol(PTR);
  auto lhsVal = getValueSym(lhs);
  auto rhsVal = getValueSym(rhs);
  auto addCon = mkEq(resVal, mkPlus(lhsVal, rhsVal));
  symbolicMemory[resPtr] = pair<const Symbol*, Constraint*>(resVal, addCon);
  return resPtr;
}

const Symbol* Engine::executeSub(const Symbol* lhs, const Symbol* rhs) {
  auto resVal = mkSymbol(INT_32);
  auto resPtr = mkSymbol(PTR);
  auto lhsVal = getValueSym(lhs);
  auto rhsVal = getValueSym(rhs);
  auto subCon = mkEq(resVal, mkMinus(lhsVal, rhsVal));
  symbolicMemory[resPtr] = pair<Symbol*, Constraint*>(resVal, subCon);
  return resPtr;
}

const Symbol* Engine::executeMul(const Symbol* lhs, const Symbol* rhs) {
  auto resVal = mkSymbol(INT_32);
  auto resPtr = mkSymbol(PTR);
  auto lhsVal = getValueSym(lhs);
  auto rhsVal = getValueSym(rhs);
  auto subCon = mkEq(resVal, mkTimes(lhsVal, rhsVal));
  symbolicMemory[resPtr] = pair<Symbol*, Constraint*>(resVal, subCon);
  return resPtr;
}

const Symbol* Engine::allocateStack(SymbolType t) {
  auto a = addSymbol(t);
  auto b = mkSymbol(PTR);
  auto bVal = mkSymbol(PTR);
  auto bConstraint = mkEq(bVal, a);
  symbolicMemory[b] = pair<Symbol*, Constraint*>(bVal, bConstraint);
  return b;
}

void Engine::executeStore(const Symbol* val, const Symbol* locationPtr) {
  auto v = getValueSym(val);
  auto recLoc = addrPointedToBy(locationPtr);
  auto recLocVal = getValueSym(recLoc);
  setConstraint(recLoc, mkEq(recLocVal, v));
  return;
}

const Symbol* Engine::executeLoad(const Symbol* locationPtr) {
  auto resVal = addSymbol(INT_32);
  auto loadVal = addrPointedToBy(locationPtr);
  auto loadValSym = getValueSym(loadVal);
  setConstraint(resVal, mkEq(getValueSym(resVal), loadValSym));
  return resVal;
}

OperationResult Engine::executeDiv(const Symbol* lhs, const Symbol* rhs) {
  ConstantInt32 zero(0);
  Eq denominatorIsZero(getValueSym(rhs), &zero);
  if (stateAllows(&denominatorIsZero)) {
    OperationResult opRes(true);
    return opRes;
  } else {
    OperationResult opRes(false);
    return opRes;
  }
}

void Engine::getConstraintState(vector<Constraint*>* constraintState) {
  for (auto entry : symbolicMemory) {
    auto stateConstraint = entry.second.second;
    constraintState->push_back(stateConstraint);
  }
}

bool Engine::stateImplies(Constraint* c) {
  vector<Constraint*> constraintState;
  getConstraintState(&constraintState);
  return solver->constraintsImply(&constraintState, c);
}

bool Engine::stateAllows(Constraint* c) {
  vector<Constraint*> constraintState;
  getConstraintState(&constraintState);
  return solver->constraintsAllow(&constraintState, c);
}
