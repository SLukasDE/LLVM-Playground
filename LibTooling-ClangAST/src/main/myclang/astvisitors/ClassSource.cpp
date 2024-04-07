#include "myclang/astvisitors/ClassSource.h"

#include "clang/Sema/Sema.h"                               // clang::Sema

#include <iostream>

namespace myclang {
namespace astvisitors {

ClassSource::ClassSource(clang::ASTUnit& aAstUnit)
: astUnit(aAstUnit),
  astContext(aAstUnit.getASTContext())
{ }
/*
void ClassSource::myTraverseTU() {
	this->TraverseDecl(astContext.getTranslationUnitDecl());
}
*/
bool ClassSource::VisitCXXRecordDecl(clang::CXXRecordDecl* recordDecl) {
	if (recordDecl->getDefinition() != recordDecl) {
		// This is not the definition, so ignore it.
	}
	else {
		std::cout << recordDecl->Decl::getDeclKindName()
			<< " \"" << recordDecl->getQualifiedNameAsString()
			<< "\" at " << declLocStr(*recordDecl)
			<< ":\n";

		// Without this, the implicit members are not in the AST.
		astUnit.getSema().ForceDeclarationOfImplicitMembers(recordDecl);
	}

	return true;
}

bool ClassSource::VisitCXXConstructorDecl(clang::CXXConstructorDecl* ctor) {
	std::cout << "  " << ctor->Decl::getDeclKindName()
		<< " \"" << ctor->getQualifiedNameAsString()
		<< "\" type=\"" << typeStr(ctor->getType())
		<< "\" at "
		<< declLocStr(*ctor)
		<< ": deleted=" << ctor->isDeleted()
		<< "\n";

	return true;
}


std::string ClassSource::declLocStr(const clang::Decl& decl) {
	return decl.getLocation().printToString(astContext.getSourceManager());
}

std::string ClassSource::typeStr(clang::QualType qualType) {
	return qualType.getAsString();
}

} /* namespace astvisitors */
} /* namespace myclang */
