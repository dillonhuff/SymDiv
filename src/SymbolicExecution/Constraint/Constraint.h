#ifndef CONSTRAINT_H
#define CONSTRAINT_H

enum ConstraintKind {
  EQ,
  TRUE,
  FALSE
};

class Constraint {
 protected:
  ConstraintKind kind;

 public:
  virtual bool operator==(const Constraint& other) const;
  ConstraintKind getKind() const;
  virtual bool isBinaryPredicate() const { return false; }
};

#endif
