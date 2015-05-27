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

  bool isSymbol() const { return kind == SYMBOL; }
  bool isConstantInt32() const { return kind == CONSTANT_VALUE; }
  bool isPlus() const { return kind == PLUS; }
  bool isDivide() const { return kind == DIVIDE; }
  bool isTimes() const { return kind == TIMES; }
  bool isMinus() const { return kind == MINUS; }
  bool isBinaryFunction() const { return (kind == TIMES) || (kind == PLUS) || (kind == DIVIDE) || (kind == MINUS); }

  virtual bool operator==(const Term* other) const;

  virtual std::string toString() const { throw; }
};

#endif
