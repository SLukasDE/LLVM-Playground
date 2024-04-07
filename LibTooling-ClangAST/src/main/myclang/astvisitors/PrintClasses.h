#ifndef MYCLANG_ASTVISITORS_PRINTCLASSES_H_
#define MYCLANG_ASTVISITORS_PRINTCLASSES_H_

#include "clang/AST/DeclCXX.h"                             // clang::CXXRecordDecl
#include "clang/AST/RecursiveASTVisitor.h"                 // clang::RecursiveASTVisitor

#include "llvm/Support/raw_ostream.h"                      // llvm::raw_ostream

#include <string>

namespace myclang {
namespace astvisitors {

class PrintClasses : public clang::RecursiveASTVisitor<PrintClasses>
{
public:
	PrintClasses();

	bool VisitCXXRecordDecl(clang::CXXRecordDecl* decl);

private:
	//bool processCXXMethod(clang::CXXMethodDecl* decl);
	std::string newLine();

	llvm::raw_ostream& ostream;
	std::string indent;
	int indentLevel = 0;
};

} /* namespace astvisitors */
} /* namespace myclang */

#endif /* MYCLANG_ASTVISITORS_PRINTCLASSES_H_ */
