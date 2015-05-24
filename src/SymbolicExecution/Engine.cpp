#include "SymbolicExecution/Constraint/Eq.h"
#include "SymbolicExecution/Constraint/Plus.h"
#include "SymbolicExecution/Constraint/True.h"
#include "SymbolicExecution/Engine.h"

#include <iostream>

using namespace std;

Engine::Engine() {
  nextSymId = 0;
}

Engine::~Engine() {
  //  for (auto symPtr : allSymbols) {
  //    Symbol ptr = symPtr;
    //    delete symPtr;
  //  }
}

Constraint* Engine::mkEq(const Term& lhs, const Term& rhs) {
  auto eq = new Eq(lhs, rhs);
  allConstraints.push_back(eq);
  return eq;
}

Term* Engine::mkPlus(const Term& lhs, const Term& rhs) {
  auto plus = new Plus(lhs, rhs);
  allTerms.push_back(plus);
  return plus;
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

const Symbol& Engine::addSymbol(SymbolType t) {
  auto sVal = mkSymbol(t);
  auto sPtr = mkSymbol(PTR);
  symbolicMemory[*sPtr] = pair<Symbol*, Constraint*>(sVal, mkTrue());
  return *sPtr;
}

const Constraint& Engine::getConstraint(Symbol& s) const {
  auto m = symbolicMemory;
  auto symValConstraintPair = m[s];
  return *(symValConstraintPair.second);
}

const Symbol& Engine::executeBinop(OpCode c, const Symbol& lhs, const Symbol& rhs) {
  auto resVal = mkSymbol(INT_32);
  auto resPtr = mkSymbol(PTR);
  auto addCon = mkEq(*resVal, *mkPlus(lhs, rhs));
  symbolicMemory[*resPtr] = pair<Symbol*, Constraint*>(resVal, addCon);
  return *resPtr;
}
