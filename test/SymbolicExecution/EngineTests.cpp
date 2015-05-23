#include "llvm/IR/LLVMContext.h"

#include "SymbolicExecution/Engine.h"
#include "SymbolicExecution/EngineTests.h"

#include <iostream>

using namespace std;
using namespace llvm;

void initializeEngine() {
  Engine e;
  auto dummyContext = new LLVMContext();
}

void runEngineTests() {
  cout << "--------------------- Starting Engine Tests ---------------------" << endl;
  initializeEngine();
  cout << "-----------------------------------------------------------------" << endl;
}
