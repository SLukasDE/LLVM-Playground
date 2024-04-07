#include "myclang/astvisitors/PrintClasses.h"

namespace myclang {
namespace astvisitors {

PrintClasses::PrintClasses()
: ostream(llvm::outs()),
  indent(" ")
{}

bool PrintClasses::VisitCXXRecordDecl(clang::CXXRecordDecl* decl) {
	ostream << "class " << decl->getNameAsString() << "\n{\n";
	++indentLevel;
	for(clang::DeclContext::decl_iterator pos = decl->decls_begin(); pos != decl->decls_end(); ++pos) {
		//handle different decls here!
	}
	ostream << "};\n";
	--indentLevel;
	return true;
}

/*
bool PrintClasses::processCXXMethod(clang::CXXMethodDecl* cxxMethodDecl) {
	//output the return type
	ostream << cxxMethodDecl->getResultType().getAsString() << " " << cxxMethodDecl->getNameAsString() << "("
	//output parameters here
	<< ");\n";
	return true;
}
*/

std::string PrintClasses::newLine() {
	std::string retval = "\n";
	for (int n = 1; n <= indentLevel; ++n) {
		retval += indent;
	}
	return retval;
}

} /* namespace astvisitors */
} /* namespace myclang */
