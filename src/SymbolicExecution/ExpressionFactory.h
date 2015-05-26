#ifndef EXPRESSION_FACTORY_H
#define EXPRESSION_FACTORY_H

#include "SymbolicExecution/Constraint/Constraint.h"
#include "SymbolicExecution/Constraint/Term.h"

#include <memory>
#include <vector>

class ExpressionFactory {
 protected:
std::vector<std::unique_ptr<Constraint>> allConstraints;
std::vector<std::unique_ptr<Term>> allTerms;
  int nextSymId;

 public:
ExpressionFactory();
  Constraint* mkTrue();
  Constraint* mkEq(const Term* lhs, const Term* rhs);
  Term* mkPlus(const Term* lhs, const Term* rhs);
  Term* mkMinus(const Term* lhs, const Term* rhs);
  Term* mkTimes(const Term* lhs, const Term* rhs);
  Term* mkConstantInt32(int val);
  Symbol* mkSymbol(SymbolType t);

};

#endif
