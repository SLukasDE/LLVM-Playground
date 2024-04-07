#include "myclang/ast_matchers/MatchDecls.h"

#include "clang/AST/ASTContext.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Basic/SourceManager.h"

#include <iostream>
#include <string>

namespace myclang {
namespace ast_matchers {

MatchDecls::MatchDecls(bool showDetails)
: callback(showDetails),
  classMatcher(clang::ast_matchers::cxxRecordDecl(
		  clang::ast_matchers::decl().bind("idXYZ"),
		  clang::ast_matchers::hasAttr(clang::attr::Annotate))),
  propertyMatcher(clang::ast_matchers::fieldDecl(
		  clang::ast_matchers::decl().bind("id"),
		  clang::ast_matchers::hasAttr(clang::attr::Annotate))),
  functionMatcher(clang::ast_matchers::functionDecl(
		  clang::ast_matchers::decl().bind("id"),
		  clang::ast_matchers::hasAttr(clang::attr::Annotate)))
  /*functionMatcher2(clang::ast_matchers::functionDecl(
			clang::ast_matchers::decl().bind("function-id"),
			clang::ast_matchers::hasAnyParameter(clang::ast_matchers::hasType(clang::ast_matchers::recordDecl(clang::ast_matchers::matchesName("std::vector"))))))
  */
{
	finder.addMatcher(classMatcher,    &callback);
	finder.addMatcher(propertyMatcher, &callback);
	finder.addMatcher(functionMatcher, &callback);

	toolAction = clang::tooling::newFrontendActionFactory(&finder);
}

clang::tooling::FrontendActionFactory& MatchDecls::getToolAction() {
	return *toolAction;
}



MatchDecls::MatchCallback::MatchCallback(bool aShowDetails)
: showDetails(aShowDetails)
{ }

void MatchDecls::MatchCallback::run(clang::ast_matchers::MatchFinder::MatchResult const& result) {
	clang::CXXRecordDecl const* record = result.Nodes.getNodeAs<clang::CXXRecordDecl>("idXYZ");
	if(record) {
		foundRecord(*record);
		return;
	}

	clang::FieldDecl const* field = result.Nodes.getNodeAs<clang::FieldDecl>("id");
	if(field) {
		foundField(*field);
		return;
	}

	clang::FunctionDecl const* function = result.Nodes.getNodeAs<clang::FunctionDecl>("id");
	if(function) {
		foundFunction(*function);
		return;
	}
}

void MatchDecls::MatchCallback::onStartOfTranslationUnit() {
}

void MatchDecls::MatchCallback::onEndOfTranslationUnit() {
}

void MatchDecls::MatchCallback::foundRecord(const clang::CXXRecordDecl& record) {
	if(showDetails) {
		clang::SourceManager& sourceManager = record.getASTContext().getSourceManager();
		clang::SourceLocation sourceLocation = record.getLocation();
		std::string filename = sourceManager.getFilename(sourceLocation);
		std::cout << "Found record\n";
		std::cout << "------------\n";
		std::cout << "  - filename: \"" << filename << "\"\n";
		std::cout << "  - class   : \"" << record.getNameAsString() << "\"\n";

		std::cout << "  - getName():         \"" << record.getName().data() << "\"\n";
		std::cout << "  - getNameAsString(): \"" << record.getNameAsString() << "\"\n";
		std::cout << "  - getDeclName().getAsString(): \"" << record.getDeclName().getAsString() << "\"\n";
		std::cout << "  - getQualifiedNameAsString():  \"" << record.getQualifiedNameAsString() << "\"\n";
		clang::FileManager& fileManager = sourceManager.getFileManager();
		//fileManager.getNumUniqueRealFiles();
	}
}

void MatchDecls::MatchCallback::foundField(const clang::FieldDecl& field) {
	field.dump();
}

void MatchDecls::MatchCallback::foundFunction(const clang::FunctionDecl& function) {
	function.dump();
}

} /* namespace ast_matchers */
} /* namespace myclang */
