#ifndef TIMES_H
#define TIMES_H

class Times : public BinaryFunction {
 public:
  Times(const Term* l, const Term* r)
    : BinaryFunction::BinaryFunction(l, r) {
    kind = TIMES;
  }

  virtual bool operator==(const Term* other) const {
    return BinaryFunction::operator==(other); 
  }

  bool isTimes() const override { return true; }
};

#endif
