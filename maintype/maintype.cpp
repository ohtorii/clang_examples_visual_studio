#include <llvm/Support/Host.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/Decl.h>
#include <clang/AST/DeclGroup.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Parse/ParseAST.h>

struct ast_consumer : clang::ASTConsumer {
    void HandleTopLevelDecl(clang::DeclGroupRef group) {
        for (auto it = group.begin(); it != group.end(); ++it) {
            if (auto const* fn = llvm::dyn_cast<clang::FunctionDecl>(*it)) {
                check(*fn);
            }
        }
    }

private:
    void check(clang::FunctionDecl const& fn) const {
        if (fn.isMain()) {
            if (fn.param_size() > 0) {
                llvm::outs() << "main has some arguments.\n";
            } else {
                llvm::outs() << "main doesn't have any arguments.\n";
            }
        }
    }
};

int main(int argc, char** argv) {
    clang::CompilerInstance compiler;

    compiler.createDiagnostics(argc, argv);
    compiler.getInvocation().setLangDefaults(clang::IK_CXX);
    clang::CompilerInvocation::CreateFromArgs(
        compiler.getInvocation(),
        argv + 1, argv + argc,
        compiler.getDiagnostics()
    );

    compiler.setTarget(
        clang::TargetInfo::CreateTargetInfo(
            compiler.getDiagnostics(),
            compiler.getTargetOpts()
        )
    );

    compiler.createFileManager();
    compiler.createSourceManager(compiler.getFileManager());
    compiler.createPreprocessor();
    compiler.createASTContext();
    compiler.setASTConsumer(new ast_consumer);
    compiler.createSema(false, NULL);

    auto const n = compiler.getFrontendOpts().Inputs.size();
    if (n == 0) {
        llvm::errs() << "No input file.\n";
        return 1;
    } else if (n > 1) {
        llvm::errs() << "There are too many inputs.\n";
        return 1;
    }

    compiler.InitializeSourceManager(
        compiler.getFrontendOpts().Inputs[0].second
    );

    clang::ParseAST(
        compiler.getPreprocessor(),
        &compiler.getASTConsumer(),
        compiler.getASTContext()
    );

    return 0;
}
