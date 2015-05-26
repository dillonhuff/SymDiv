#include "ClangInterface/FunctionChecking.h"

#include "clang/CodeGen/CodeGenAction.h"
#include "clang/Basic/DiagnosticOptions.h"
#include "clang/Driver/Compilation.h"
#include "clang/Driver/Driver.h"
#include "clang/Driver/Tool.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/CompilerInvocation.h"
#include "clang/Frontend/FrontendDiagnostic.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"

#include <cstdio>
#include <memory>

using namespace clang;
using namespace clang::driver;

std::string GetExecutablePath(const char *Argv0) {
  void *MainAddr = (void*) (intptr_t) GetExecutablePath;
  return llvm::sys::fs::getMainExecutable(Argv0, MainAddr);
}

int main(int argc, const char **argv, char * const *envp) {
  void *MainAddr = (void*) (intptr_t) GetExecutablePath;
  std::string Path = GetExecutablePath(argv[0]);
  IntrusiveRefCntPtr<DiagnosticOptions> DiagOpts = new DiagnosticOptions();
  TextDiagnosticPrinter *DiagClient =
    new TextDiagnosticPrinter(llvm::errs(), &*DiagOpts);
  IntrusiveRefCntPtr<DiagnosticIDs> DiagID(new DiagnosticIDs());
  DiagnosticsEngine Diags(DiagID, &*DiagOpts, DiagClient);

  std::string TripleStr = llvm::sys::getProcessTriple();
  llvm::Triple T(TripleStr);
  if (T.isOSBinFormatCOFF())
    T.setObjectFormat(llvm::Triple::ELF);
  Driver TheDriver(Path, T.str(), Diags);
  TheDriver.setTitle("clang interpreter");
  TheDriver.setCheckInputsExist(false);

  SmallVector<const char *, 16> Args(argv, argv + argc);
  Args.push_back("-fsyntax-only");
  std::unique_ptr<Compilation> C(TheDriver.BuildCompilation(Args));
  if (!C)
    return 0;

  const driver::JobList &Jobs = C->getJobs();
  if (Jobs.size() != 1 || !isa<driver::Command>(*Jobs.begin())) {
    SmallString<256> Msg;
    llvm::raw_svector_ostream OS(Msg);
    Jobs.Print(OS, "; ", true);
    Diags.Report(diag::err_fe_expected_compiler_job) << OS.str();
    return 1;
  }
  const driver::Command &Cmd = cast<driver::Command>(*Jobs.begin());
  if (llvm::StringRef(Cmd.getCreator().getName()) != "clang") {
    Diags.Report(diag::err_fe_expected_clang_command);
    return 1;
  }

  const driver::ArgStringList &CCArgs = Cmd.getArguments();
  std::unique_ptr<CompilerInvocation> CI(new CompilerInvocation);
  CompilerInvocation::CreateFromArgs(*CI,
				     const_cast<const char **>(CCArgs.data()),
				     const_cast<const char **>(CCArgs.data()) +
				     CCArgs.size(),
				     Diags);

  if (CI->getHeaderSearchOpts().Verbose) {
    llvm::errs() << "clang invocation:\n";
    Jobs.Print(llvm::errs(), "\n", true);
    llvm::errs() << "\n";
  }

  CompilerInstance Clang;
  Clang.setInvocation(CI.release());

  Clang.createDiagnostics();
  if (!Clang.hasDiagnostics())
    return 1;

  if (Clang.getHeaderSearchOpts().UseBuiltinIncludes &&
      Clang.getHeaderSearchOpts().ResourceDir.empty())
    Clang.getHeaderSearchOpts().ResourceDir =
      CompilerInvocation::GetResourcesPath(argv[0], MainAddr);

  std::unique_ptr<CodeGenAction> Act(new EmitLLVMOnlyAction());
  if (!Clang.ExecuteAction(*Act))
    return 1;

  if (std::unique_ptr<llvm::Module> Module = Act->takeModule()) {
    for (auto& f : Module.get()->getFunctionList()) {
      checkFunction(&f);
    }
  }

  llvm::llvm_shutdown();
  return 0;
}
