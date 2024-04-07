#include "myclang/astvisitors/NamedClass.h"

#include "llvm/Support/raw_ostream.h"                      // llvm::raw_ostream

namespace myclang {
namespace astvisitors {

NamedClass::NamedClass(clang::ASTContext& aASTContext)
: astContext(aASTContext)
{ }

// see https://stackoverflow.com/questions/71318084/how-visitnameddecl-and-visitcxxrecorddecl-are-called-by-recursiveastvisitor
bool NamedClass::VisitCXXRecordDecl(clang::CXXRecordDecl* recordDecl) {
	if (recordDecl->getQualifiedNameAsString() == "n::m::C") {
		clang::FullSourceLoc fullLocation = astContext.getFullLoc(recordDecl->getBeginLoc());
		if (fullLocation.isValid()) {
			llvm::outs() << "Found declaration at " << fullLocation.getSpellingLineNumber() << ":" << fullLocation.getSpellingColumnNumber() << "\n";
		}
	}
	return true;
}

} /* namespace astvisitors */
} /* namespace myclang */
