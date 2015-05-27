#ifndef PTR_H
#define PTR_H

#include "SymbolicExecution/Type/Type.h"

class Ptr : public Type {
 protected:
  const Type* pointedTo;

 public:
  Ptr(const Type* t)
    : pointedTo(t) {}

  const Type* typePointedTo() const { return pointedTo; }
};

#endif
