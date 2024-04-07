#ifndef MYCLANG_ASTFRONTENDACTIONS_PARSEDTEMPLATES_H_
#define MYCLANG_ASTFRONTENDACTIONS_PARSEDTEMPLATES_H_

#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"

#include "llvm/Support/raw_ostream.h"

#include <memory>
#include <set>
#include <string>

namespace myclang {
namespace astfrontendactions {

class ParsedTemplates : public clang::PluginASTAction {
protected:
	std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& compilerInstance, llvm::StringRef) override;
	bool ParseArgs(const clang::CompilerInstance& ci, const std::vector<std::string>& args) override;

private:
	std::set<std::string> parsedTemplates;

	void printHelp(llvm::raw_ostream& ros);
};

} /* namespace astfrontendactions */
} /* namespace myclang */

#endif /* MYCLANG_ASTFRONTENDACTIONS_PARSEDTEMPLATES_H_ */
