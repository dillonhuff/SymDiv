#include "SymbolicExecution/Constraint/ConstantInt32.h"
#include "SymbolicExecution/Constraint/Eq.h"
#include "SymbolicExecution/Constraint/Minus.h"
#include "SymbolicExecution/Constraint/Plus.h"
#include "SymbolicExecution/Constraint/Symbol.h"
#include "SymbolicExecution/Constraint/Times.h"
#include "SymbolicExecution/Constraint/True.h"
#include "SymbolicExecution/ExpressionFactory.h"
#include "SymbolicExecution/Type/TypeSystem.h"

#include <vector>

using namespace std;

ExpressionFactory::ExpressionFactory() {
  nextSymId = 0;
}

Constraint* ExpressionFactory::mkEq(const Term* lhs, const Term* rhs) {
  auto eq = new Eq(lhs, rhs);
  allConstraints.push_back(std::unique_ptr<Constraint>(eq));
  return eq;
}

Term* ExpressionFactory::mkPlus(const Term* lhs, const Term* rhs) {
  auto plus = new Plus(lhs, rhs);
  allTerms.push_back(std::unique_ptr<Term>(plus));
  return plus;
}

Term* ExpressionFactory::mkMinus(const Term* lhs, const Term* rhs) {
  auto minus = new Minus(lhs, rhs);
  allTerms.push_back(std::unique_ptr<Term>(minus));
  return minus;
}

Term* ExpressionFactory::mkConstantInt32(int val) {
  auto constant = new ConstantInt32(val);
  allTerms.push_back(std::unique_ptr<Term>(constant));
  return constant;
}

Term* ExpressionFactory::mkTimes(const Term* lhs, const Term* rhs) {
  auto times = new Times(lhs, rhs);
  allTerms.push_back(std::unique_ptr<Term>(times));
  return times;
}

Symbol* ExpressionFactory::mkSymbol(const Type* t) {
  auto s = new Symbol(t, nextSymId);
  nextSymId++;
  allTerms.push_back(std::unique_ptr<Term>(s));
  return s;
}

Type* ExpressionFactory::mkPtr(const Type* t) {
  auto ptr = new Ptr(t);
  allTypes.push_back(std::unique_ptr<Type>(ptr));
  return ptr;
}

Type* ExpressionFactory::mkInt(int width) {
  auto i = new Integer(width);
  allTypes.push_back(std::unique_ptr<Type>(i));
  return i;
}

Constraint* ExpressionFactory::mkTrue() {
  auto t = new True();
  allConstraints.push_back(std::unique_ptr<Constraint>(t));
  return t;
}
