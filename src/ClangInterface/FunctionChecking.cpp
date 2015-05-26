#include "ClangInterface/FunctionChecking.h"
#include "SymbolicExecution/Constraint/Symbol.h"
#include "SymbolicExecution/Engine.h"
#include "SymbolicExecution/ExpressionFactory.h"
#include "SymbolicExecution/Z3Solver.h"

#include "llvm/Support/raw_ostream.h"

#include <iostream>
#include <map>

using namespace std;

void addArguments(llvm::Function* f, Engine* e, map<llvm::Value*, const Symbol*>* valSyms) {
  for (auto& arg : f->getArgumentList()) {
    (*valSyms)[&arg] = e->addSymbol(INT_32);
  }
  return;
}

bool executeAlloca(llvm::Instruction* instr, llvm::Function* f, Engine* e, map<llvm::Value*, const Symbol*>* valSyms) {
  auto s = e->allocateStack(INT_32);
  (*valSyms)[instr] = s;
  return false;
}

bool executeStore(llvm::Instruction* instr, llvm::Function* f, Engine* e, map<llvm::Value*, const Symbol*>* valSyms) {
  auto toStore = (*valSyms)[instr->getOperand(0)];
  auto storePtr = (*valSyms)[instr->getOperand(1)];
  e->executeStore(toStore, storePtr);
  return false;
}

bool executeLoad(llvm::Instruction* instr, llvm::Function* f, Engine* e, map<llvm::Value*, const Symbol*>* valSyms) {
  auto loadPtr = (*valSyms)[instr->getOperand(0)];
  auto recVal = e->executeLoad(loadPtr);
  (*valSyms)[instr] = recVal;
  return false;
}

bool executeSDiv(llvm::Instruction* instr, llvm::Function* f, Engine* e, map<llvm::Value*, const Symbol*>* valSyms) {
  auto lhs = (*valSyms)[instr->getOperand(0)];
  auto rhs = (*valSyms)[instr->getOperand(1)];
  auto opRes = e->executeDiv(lhs, rhs);
  return opRes.errorIsPossible();
}

bool executeAdd(llvm::Instruction* instr, llvm::Function* f, Engine* e, map<llvm::Value*, const Symbol*>* valSyms) {
  auto lhs = (*valSyms)[instr->getOperand(0)];
  auto rhs = (*valSyms)[instr->getOperand(1)];
  auto result = e->executeBinop(ADD, lhs, rhs);
  (*valSyms)[instr] = result;
  return false;
}

bool executeInstruction(llvm::Instruction* instr, llvm::Function* f, Engine* e, map<llvm::Value*, const Symbol*>* valSyms) {
  if (instr->isTerminator()) {
    return false;
  }
  switch(instr->getOpcode()) {
  case(llvm::Instruction::Alloca):
    return executeAlloca(instr, f, e, valSyms);
  case(llvm::Instruction::Store):
    return executeStore(instr, f, e, valSyms);
  case(llvm::Instruction::Load):
    return executeLoad(instr, f, e, valSyms);
  case(llvm::Instruction::SDiv):
    return executeSDiv(instr, f, e, valSyms);
  case(llvm::Instruction::Add):
    return executeAdd(instr, f, e, valSyms);
  default:
    llvm::errs() << "Error: Unsupported opcode " << instr->getOpcodeName();
    throw;
  }
  return true;
}

void reportDivZero(llvm::Instruction* instr, Engine* e) {
  llvm::errs() << "Error found div by zero\n";
  llvm::errs() << e->toString() << "\n";
}

void executeBody(llvm::Function* f, Engine* e, map<llvm::Value*, const Symbol*>* valSyms) {
  for (auto& bb : f->getBasicBlockList()) {
    for (auto& instr : bb) {
      bool foundError = executeInstruction(&instr, f, e, valSyms);
      if (foundError) {
	reportDivZero(&instr, e);
	return;
      }
    }
  }
  cout << "Function is clean" << endl;
}

void checkFunction(llvm::Function* f) {
  Z3Solver solver;
  ExpressionFactory fac;
  Engine e(&solver, &fac);
  map<llvm::Value*, const Symbol*> valSyms;
  addArguments(f, &e, &valSyms);
  executeBody(f, &e, &valSyms);
  return;
}
