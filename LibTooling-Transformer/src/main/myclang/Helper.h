#ifndef MYCLANG_HELPER_H_
#define MYCLANG_HELPER_H_

#include <clang/Frontend/FrontendActions.h>
#include "clang/Tooling/CompilationDatabase.h"
#include <clang/Tooling/Tooling.h>

#include <llvm/ADT/StringRef.h>
#include <llvm/ADT/Twine.h>

#include <memory>
#include <string>
#include <vector>

namespace myclang {

struct Helper {
	Helper() = delete;

    static std::vector<std::string> getSyntaxOnlyToolArgs(const std::vector<std::string>& extraArgs, llvm::StringRef fileName);

    static bool customRunToolOnCodeWithArgs(std::unique_ptr<clang::FrontendAction> frontendAction, const llvm::Twine& code,
                                     const std::vector<std::string>& args, const llvm::Twine& fileName,
                                     const clang::tooling::FileContentMappings& virtualMappedFiles = clang::tooling::FileContentMappings());

    static bool fileExists(const std::string& file);
    static std::vector<std::string> getCompileArgs(const std::vector<clang::tooling::CompileCommand>& compileCommands);
    static std::string getSourceCode(const std::string& sourceFile);
    static std::string getClangBuiltInIncludePath(const std::string& fullCallPath);
};

} /* namespace myclang */

#endif /* MYCLANG_HELPER_H_ */
