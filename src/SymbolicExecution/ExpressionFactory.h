#ifndef EXPRESSION_FACTORY_H
#define EXPRESSION_FACTORY_H

#include "SymbolicExecution/Constraint/Constraint.h"
#include "SymbolicExecution/Constraint/Term.h"

#include <vector>

class ExpressionFactory {
 protected:
std::vector<Constraint*> allConstraints;
std::vector<Term*> allTerms;
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
