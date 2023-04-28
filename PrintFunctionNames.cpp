#include "clang/Frontend/FrontendPluginRegistry.h"
//#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"
#include "llvm/Support/raw_ostream.h"
#include "clang/Format/Format.h"
using namespace clang;

namespace {
class PrintFunctionsConsumer : public ASTConsumer {
public:
  PrintFunctionsConsumer() = default;
  bool HandleTopLevelDecl(DeclGroupRef DG) override { return true; }
  void HandleTranslationUnit(ASTContext& context) override {
    auto  style = clang::format::getLLVMStyle(); // <<-------- PROBLEM ...
  }
};

class PrintFunctionNamesAction : public PluginASTAction {
protected:
  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, llvm::StringRef) override {
    return std::make_unique<PrintFunctionsConsumer>();
  }

 //PluginASTAction::ActionType getActionType() override { return AddBeforeMainAction; }
 PluginASTAction::ActionType getActionType() override { return ReplaceAction; }
 bool ParseArgs(const CompilerInstance &CI, const std::vector<std::string> &args) override { return true; }
 void PrintHelp(llvm::raw_ostream& ros) { }
};
}

static FrontendPluginRegistry::Add<PrintFunctionNamesAction>
X("print-fns", "print function names");
