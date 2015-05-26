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
  TIMES,
  DIVIDE
};

std::string termKindToString(TermKind k);

class Term {
 protected:
  TermKind kind;

 public:
  virtual ~Term() {}

  virtual bool isSymbol() const { return false; }
  virtual bool isConstantInt32() const { return false; }
  virtual bool isPlus() const { return false; }
  virtual bool isDivide() const { return false; }
  virtual bool isMinus() const { return false; }
  virtual bool isBinaryFunction() const { return false; }

  virtual bool operator==(const Term& other) const;
  virtual bool operator==(const Term* other) const;

  virtual std::string toString() const { throw; }
};

#endif
