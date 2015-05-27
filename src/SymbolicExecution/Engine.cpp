#include "SymbolicExecution/Constraint/ConstantInt32.h"
#include "SymbolicExecution/Constraint/Eq.h"
#include "SymbolicExecution/Constraint/Minus.h"
#include "SymbolicExecution/Constraint/Plus.h"
#include "SymbolicExecution/Constraint/Times.h"
#include "SymbolicExecution/Constraint/True.h"
#include "SymbolicExecution/Engine.h"
#include "SymbolicExecution/Type/TypeSystem.h"

#include <iostream>

using namespace std;

Engine::Engine(ConstraintSolver* s, ExpressionFactory* factory) {
  solver = s;
  f = factory;
}


const Symbol* Engine::addSymbol(const Type* t) {
  auto sVal = f->mkSymbol(t);
  auto sPtr = f->mkSymbol(f->mkPtr(t));
  symbolicMemory[sPtr] = pair<Symbol*, Constraint*>(sVal, f->mkTrue());
  return sPtr;
}

const Symbol* Engine::addConstantInt32(int val) {
  auto constVal = f->mkConstantInt32(val);
  auto sVal = f->mkSymbol(f->mkInt(32));
  auto sPtr = f->mkSymbol(f->mkPtr(f->mkInt(32)));
  symbolicMemory[sPtr] = pair<Symbol*, Constraint*>(sVal, f->mkEq(sVal, constVal));
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
  auto resVal = f->mkSymbol(f->mkInt(32));
  auto resPtr = f->mkSymbol(f->mkPtr(f->mkInt(32)));
  auto lhsVal = getValueSym(lhs);
  auto rhsVal = getValueSym(rhs);
  auto addCon = f->mkEq(resVal, f->mkPlus(lhsVal, rhsVal));
  symbolicMemory[resPtr] = pair<const Symbol*, Constraint*>(resVal, addCon);
  return resPtr;
}

const Symbol* Engine::executeSub(const Symbol* lhs, const Symbol* rhs) {
  auto resVal = f->mkSymbol(f->mkInt(32));
  auto resPtr = f->mkSymbol(f->mkPtr(f->mkInt(32)));
  auto lhsVal = getValueSym(lhs);
  auto rhsVal = getValueSym(rhs);
  auto subCon = f->mkEq(resVal, f->mkMinus(lhsVal, rhsVal));
  symbolicMemory[resPtr] = pair<Symbol*, Constraint*>(resVal, subCon);
  return resPtr;
}

const Symbol* Engine::executeMul(const Symbol* lhs, const Symbol* rhs) {
  auto resVal = f->mkSymbol(f->mkInt(32));
  auto resPtr = f->mkSymbol(f->mkPtr(f->mkInt(32)));
  auto lhsVal = getValueSym(lhs);
  auto rhsVal = getValueSym(rhs);
  auto subCon = f->mkEq(resVal, f->mkTimes(lhsVal, rhsVal));
  symbolicMemory[resPtr] = pair<Symbol*, Constraint*>(resVal, subCon);
  return resPtr;
}

const Symbol* Engine::allocateStack(const Type* t) {
  auto a = addSymbol(t);
  auto b = f->mkSymbol(f->mkPtr(t));
  auto bVal = f->mkSymbol(f->mkPtr(t));
  auto bConstraint = f->mkEq(bVal, a);
  symbolicMemory[b] = pair<Symbol*, Constraint*>(bVal, bConstraint);
  return b;
}

void Engine::executeStore(const Symbol* val, const Symbol* locationPtr) {
  auto v = getValueSym(val);
  auto recLoc = addrPointedToBy(locationPtr);
  auto recLocVal = getValueSym(recLoc);
  setConstraint(recLoc, f->mkEq(recLocVal, v));
  return;
}

const Symbol* Engine::executeLoad(const Symbol* locationPtr) {
  auto resVal = addSymbol(f->mkInt(32));
  auto loadVal = addrPointedToBy(locationPtr);
  auto loadValSym = getValueSym(loadVal);
  setConstraint(resVal, f->mkEq(getValueSym(resVal), loadValSym));
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

std::string Engine::toString() const {
  std::string out = "";
  for (auto entry : symbolicMemory) {
    out += entry.first->toString();
    out += "\t->\t(" + entry.second.first->toString();
    out += + ", " + entry.second.second->toString() + ")\n";
  }
  return out;
}
