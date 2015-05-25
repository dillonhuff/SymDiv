#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "SymbolicExecution/Constraint/Constraint.h"

#include <iostream>

void testResult(bool res, std::string testName);
void test(const Constraint* expected, const Constraint* actual);
void testNEQ(const Constraint* expected, const Constraint* actual);

#endif
