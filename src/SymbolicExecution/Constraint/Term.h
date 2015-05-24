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
  virtual bool isSymbol() const { return false; }
  virtual bool isBinaryFunction() const { return false; }
  virtual bool operator==(const Term& other) const;
  virtual bool operator==(const Term* other) const;
};

#endif
