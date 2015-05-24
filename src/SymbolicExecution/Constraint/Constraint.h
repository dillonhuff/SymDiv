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
  bool operator==(const Constraint& other) const;
  ConstraintKind getKind() const;
};

#endif
