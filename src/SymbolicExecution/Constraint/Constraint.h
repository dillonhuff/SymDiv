#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <string>

enum ConstraintKind {
  EQ,
  TRUE,
  FALSE
};

std::string constraintKindToString(ConstraintKind k);

class Constraint {
 protected:
  ConstraintKind kind;

 public:
  virtual bool operator==(const Constraint& other) const;
  virtual bool operator==(const Constraint* other) const;
  ConstraintKind getKind() const;
  virtual bool isBinaryPredicate() const { return false; }

  virtual std::string toString() const { throw; }
};

#endif
