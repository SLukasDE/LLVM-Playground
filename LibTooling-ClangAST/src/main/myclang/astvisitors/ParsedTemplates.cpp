#include "myclang/astvisitors/ParsedTemplates.h"

namespace myclang {
namespace astvisitors {

ParsedTemplates::ParsedTemplates(const std::set<std::string>& aParsedTemplates)
: parsedTemplates(aParsedTemplates)
{}

// see https://stackoverflow.com/questions/71318084/how-visitnameddecl-and-visitcxxrecorddecl-are-called-by-recursiveastvisitor
bool ParsedTemplates::VisitFunctionDecl(clang::FunctionDecl* functionDecl) {
	if (functionDecl->isLateTemplateParsed() && parsedTemplates.count(functionDecl->getNameAsString())) {
          lateParsedDecls.insert(functionDecl);
	}
	return true;
}

const std::set<clang::FunctionDecl*>& ParsedTemplates::getLateParsedDecls() const noexcept {
	return lateParsedDecls;
}

} /* namespace astvisitors */
} /* namespace myclang */
