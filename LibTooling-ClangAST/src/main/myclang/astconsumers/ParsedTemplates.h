#ifndef MYCLANG_ASTCONSUMERS_PARSEDTEMPLATES_H_
#define MYCLANG_ASTCONSUMERS_PARSEDTEMPLATES_H_

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/DeclGroup.h"
#include "clang/Frontend/CompilerInstance.h"

#include <set>
#include <string>

namespace myclang {
namespace astconsumers {

class ParsedTemplates : public clang::ASTConsumer {
public:
	ParsedTemplates(clang::CompilerInstance& compilerInstance, std::set<std::string> parsedTemplates);

	bool HandleTopLevelDecl(clang::DeclGroupRef declGroupRef) override;
	void HandleTranslationUnit(clang::ASTContext& astContext) override;

private:
	clang::CompilerInstance& compilerInstance;
	std::set<std::string> parsedTemplates;
};

} /* namespace astconsumers */
} /* namespace myclang */

#endif /* MYCLANG_ASTCONSUMERS_PARSEDTEMPLATES_H_ */
