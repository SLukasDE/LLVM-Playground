#ifndef MYCLANG_ASTVISITORS_NAMEDCLASS_H_
#define MYCLANG_ASTVISITORS_NAMEDCLASS_H_

#include "clang/AST/ASTContext.h"                          // clang::ASTContext
#include "clang/AST/DeclCXX.h"                             // clang::CXXRecordDecl
#include "clang/AST/RecursiveASTVisitor.h"                 // clang::RecursiveASTVisitor

namespace myclang {
namespace astvisitors {

class NamedClass : public clang::RecursiveASTVisitor<NamedClass> {
public:
	explicit NamedClass(clang::ASTContext& astContext);
	/*
		bool TraverseDecl(clang::Decl* decl) {
			// your logic here
			// Return false to stop the AST analyzing
			return RecursiveASTVisitor<ClassSource>::TraverseDecl(decl); // Forward to base class
		}
		bool TraverseStmt(clang::Stmt* statement) {
			// your logic here
			return RecursiveASTVisitor<ClassSource>::TraverseStmt(statement);
		}
		bool TraverseType(clang::QualType qualType) {
			// your logic here
			return RecursiveASTVisitor<ClassSource>::TraverseType(qualType);
		}
	*/

	// see https://stackoverflow.com/questions/71318084/how-visitnameddecl-and-visitcxxrecorddecl-are-called-by-recursiveastvisitor
	bool VisitCXXRecordDecl(clang::CXXRecordDecl* recordDecl);

private:
	clang::ASTContext& astContext;
};

} /* namespace astvisitors */
} /* namespace myclang */

#endif /* MYCLANG_ASTVISITORS_NAMEDCLASS_H_ */
