#ifndef TERM_H
#define TERM_H

#include <iostream>

enum OpCode {
  ADD,
  SUB,
  MUL,
  ALLOCATE_STACK
};

enum TermKind {
  SYMBOL,
  CONSTANT_VALUE,
  MINUS,
  PLUS,
  TIMES
};

class Term {
 protected:
  TermKind kind;

 public:
  virtual bool isSymbol() const { return false; }
  virtual bool isBinaryFunction() const { return false; }
  virtual bool operator==(const Term& other) const;
  virtual bool operator==(const Term* other) const;

  virtual std::string toString() const { throw; }
};

#endif
