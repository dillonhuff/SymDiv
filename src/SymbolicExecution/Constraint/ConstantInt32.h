#ifndef CONSTANT_INT_32_H
#define CONSTANT_INT_32_H

#include "SymbolicExecution/Constraint/Term.h"

class ConstantInt32 : public Term {
 protected:
  const int value;

 public:
  ConstantInt32(int v)
    : value(v) {}
  
  int getValue() const { return value; }

  bool operator==(const Term* other) const override;
  bool isConstantInt32() const override { return true; }

  std::string toString() const override { return std::to_string((long long int) value); }
};

#endif
