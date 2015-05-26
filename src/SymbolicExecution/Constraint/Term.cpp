#include "SymbolicExecution/Constraint/Term.h"

#include <iostream>

using namespace std;

std::string termKindToString(TermKind k) {
  switch(k) {
  case(MINUS):
    return "-";
  case(PLUS):
    return "+";
  case(TIMES):
    return "*";
  case(DIVIDE):
    return "/";
  default:
    cout << "Unsupported term kind" << endl;
    throw;
  }
}

bool Term::operator==(const Term& other) const {
  return kind == other.kind;
}

bool Term::operator==(const Term* other) const {
  return kind == other->kind;
}
