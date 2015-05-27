#ifndef INTEGER_H
#define INTEGER_H

#include "SymbolicExecution/Type/Type.h"

class Integer : public Type {
 protected:
  int width;

 public:
  Integer(int w)
    : width(w) {}
};

#endif
