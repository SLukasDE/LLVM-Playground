#ifndef MYCLANG_ASTVISITORS_PARSEDTEMPLATES_H_
#define MYCLANG_ASTVISITORS_PARSEDTEMPLATES_H_

#include "clang/AST/Decl.h"                                // clang::CXXRecordDecl
#include "clang/AST/RecursiveASTVisitor.h"                 // clang::RecursiveASTVisitor

#include <set>
#include <string>

namespace myclang {
namespace astvisitors {

class ParsedTemplates : public clang::RecursiveASTVisitor<ParsedTemplates> {
public:
	ParsedTemplates(const std::set<std::string>& aParsedTemplates);

	// see https://stackoverflow.com/questions/71318084/how-visitnameddecl-and-visitcxxrecorddecl-are-called-by-recursiveastvisitor
	bool VisitFunctionDecl(clang::FunctionDecl* functionDecl);

	const std::set<clang::FunctionDecl*>& getLateParsedDecls() const noexcept;

private:
	const std::set<std::string>& parsedTemplates;
	std::set<clang::FunctionDecl*> lateParsedDecls;
};

} /* namespace astvisitors */
} /* namespace myclang */

#endif /* MYCLANG_ASTVISITORS_PARSEDTEMPLATES_H_ */
