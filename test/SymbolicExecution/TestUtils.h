#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "SymbolicExecution/Constraint/Constraint.h"

void test(const Constraint* expected, const Constraint* actual);
void testNEQ(const Constraint* expected, const Constraint* actual);

#endif
