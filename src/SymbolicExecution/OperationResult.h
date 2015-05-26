#ifndef OPERATION_RESULT_H
#define OPERATION_RESULT_H

class OperationResult {
 protected:
  const bool possibleError;

 public:
  OperationResult(bool possibleErr)
    : possibleError(possibleErr) {}

  bool errorIsPossible() const { return possibleError; }
};

#endif
