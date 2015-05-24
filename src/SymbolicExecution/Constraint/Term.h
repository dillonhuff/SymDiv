#ifndef TERM_H
#define TERM_H

enum OpCode {
  ADD,
  SUB
};

enum TermKind {
  SYMBOL,
  CONSTANT_VALUE,
  MINUS,
  PLUS
};

class Term {
 protected:
  TermKind kind;

 public:
  virtual bool operator==(const Term& other) const { return kind == other.kind; }
};

#endif
