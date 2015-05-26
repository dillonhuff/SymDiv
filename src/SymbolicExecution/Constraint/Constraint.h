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

  virtual bool operator==(const Constraint& other) const;
  virtual bool operator==(const Constraint* other) const;
  ConstraintKind getKind() const;
  virtual bool isBinaryPredicate() const { return false; }
  virtual bool isTrue() const { return false; }
  virtual bool isFalse() const { return false; }
  virtual bool isEq() const { return false; }
  virtual bool isNEq() const { return false; }

  virtual std::string toString() const { throw; }
};

#endif
