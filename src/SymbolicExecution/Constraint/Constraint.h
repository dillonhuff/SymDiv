#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <string>

enum ConstraintKind {
  NEQ,
  EQ,
  TRUE,
  FALSE
};

std::string constraintKindToString(ConstraintKind k);

class Constraint {
 protected:
  ConstraintKind kind;

 public:
  virtual ~Constraint() {}

  virtual bool operator==(const Constraint* other) const { return getKind() == other->getKind(); }
  ConstraintKind getKind() const { return kind; }
  bool isBinaryPredicate() const { return (kind == NEQ) || (kind == EQ); }
  bool isTrue() const { return kind == TRUE; }
  bool isFalse() const { return kind == FALSE; }
  bool isEq() const { return kind == EQ; }
  bool isNEq() const { return kind == NEQ; }

  virtual std::string toString() const { throw; }
};

#endif
