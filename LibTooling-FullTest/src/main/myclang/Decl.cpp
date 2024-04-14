#include "myclang/Decl.h"
#include "myclang/QualType.h"
#include "myclang/Stmt.h"

#include "clang/AST/Expr.h"
#include "clang/AST/Type.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Lex/Lexer.h"
#include "clang/Rewrite/Core/Rewriter.h"


#include "llvm/ADT/StringRef.h"                            // llvm::StringRef
#include "llvm/Support/Casting.h"
#include "llvm/Support/raw_ostream.h"                      // llvm::raw_ostream

namespace myclang {

void Decl::dump(clang::Decl& decl, std::size_t d, clang::SourceManager& sourceManager, const clang::LangOptions& langOptions) {
	llvm::outs() << std::string(2*d, ' ') << "\n";
	llvm::outs() << std::string(2*d, ' ') << "DUMP-DECL\n";
	llvm::outs() << std::string(2*d, ' ') << "---------\n";
	const char* declKindName = decl.getDeclKindName();
	llvm::outs() << std::string(2*d, ' ') << declKindName;

	if(decl.isImplicit()) {
		llvm::outs() << " (isImplicit)";
//		return;
	}
	llvm::outs() << ":\n";

	switch (decl.getKind()) {
	case clang::Decl::Kind::Namespace:
		break;
	case clang::Decl::Kind::NamespaceAlias:
		break;
	case clang::Decl::Kind::Typedef:
		break;
	case clang::Decl::Kind::TypeAlias:
		break;
	case clang::Decl::Kind::TypeAliasTemplate:
		break;
	case clang::Decl::Kind::TemplateTypeParm:
		break;
	case clang::Decl::Kind::EnumConstant:
		break;
	case clang::Decl::Kind::Field:
		break;
	case clang::Decl::Kind::Binding:
		break;
	case clang::Decl::Kind::MSProperty:
		break;
	case clang::Decl::Kind::IndirectField:
		break;
	case clang::Decl::Kind::ObjCIvar:
		break;
	case clang::Decl::Kind::ObjCAtDefsField:
		break;
	case clang::Decl::Kind::ImplicitParam:
		break;
	case clang::Decl::Kind::ParmVar:{
		auto pvDecl = reinterpret_cast<clang::ParmVarDecl*>(&decl);
		llvm::outs() << std::string(2*d, ' ') << "  Name: '" << pvDecl->getNameAsString() << "'\n";
		llvm::outs() << std::string(2*d, ' ') << "  Type: '" << pvDecl->getType().getAsString() << "'\n";
		break;
	}
	case clang::Decl::Kind::NonTypeTemplateParm:
		break;
	case clang::Decl::Kind::ObjCCategoryImpl:
		break;
	case clang::Decl::Kind::ObjCImplementation:
		break;
	case clang::Decl::Kind::ClassScopeFunctionSpecialization:
		break;
	case clang::Decl::Kind::AccessSpec:
		break;
	case clang::Decl::Kind::LinkageSpec:
		break;
	case clang::Decl::Kind::Export:
		break;
	case clang::Decl::Kind::FileScopeAsm:
		break;
	case clang::Decl::Kind::StaticAssert:
		break;
	case clang::Decl::Kind::Block:
		break;
	case clang::Decl::Kind::Captured:
		break;
	case clang::Decl::Kind::OMPCapturedExpr:
		break;
	case clang::Decl::Kind::Label:
		break;
	case clang::Decl::Kind::CXXDeductionGuide:
		break;
	case clang::Decl::Kind::Import:
		break;
	case clang::Decl::Kind::OMPThreadPrivate:
		break;
	case clang::Decl::Kind::OMPAllocate:
		break;
	case clang::Decl::Kind::OMPDeclareReduction:
		break;
	case clang::Decl::Kind::OMPDeclareMapper:
		break;
	case clang::Decl::Kind::OMPRequires:
		break;
	case clang::Decl::Kind::ObjCTypeParam:
		break;
	case clang::Decl::Kind::BuiltinTemplate:
		break;
	case clang::Decl::Kind::PragmaComment:
		break;
	case clang::Decl::Kind::PragmaDetectMismatch:
		break;
	case clang::Decl::Kind::UsingPack:
		break;
	case clang::Decl::Kind::Concept:
		break;
	case clang::Decl::Kind::LifetimeExtendedTemporary:
		break;
	case clang::Decl::Kind::RequiresExprBody:
		break;
	case clang::Decl::Kind::Empty:
		break;
	case clang::Decl::Kind::TranslationUnit:
		break;
	case clang::Decl::Kind::ExternCContext:
		break;
	case clang::Decl::Kind::UnresolvedUsingTypename:
		break;
	case clang::Decl::Kind::UnresolvedUsingValue:
		break;
	case clang::Decl::Kind::UsingDirective:
		break;
	case clang::Decl::Kind::Enum:
		break;
	case clang::Decl::Kind::Record:
		break;
	case clang::Decl::Kind::CXXRecord:
		break;
	case clang::Decl::Kind::ClassTemplateSpecialization:
		break;
	case clang::Decl::Kind::ClassTemplatePartialSpecialization:
		break;
	case clang::Decl::Kind::Function: {
		clang::FunctionDecl* funcDecl = reinterpret_cast<clang::FunctionDecl*>(&decl);
		//auto funcDecl = llvm::cast<clang::FunctionDecl>(&decl);
		llvm::outs() << std::string(2*d, ' ') << "  Name: '" << funcDecl->getNameAsString() << "'\n";
		llvm::outs() << std::string(2*d, ' ') << "  Type: '" << funcDecl->getType().getAsString() << "'\n";
		std::string funcCall = funcDecl->getNameInfo().getName().getAsString();

		// Check for and ignore built-in functions.
		if(funcDecl->getBuiltinID() != 0) {
			break;
		}

#if 0
		for(std::size_t index = 0; index < funcDecl->param_size(); ++index) {
			llvm::ArrayRef<clang::ParmVarDecl *> parameters = funcDecl->parameters();
			if(!parameters[index]) {
				continue;
			}
			clang::ParmVarDecl& parmVarDecl = *parameters[index];
#else
		for(auto iter = funcDecl->param_begin(); iter != funcDecl->param_end(); ++iter) {
			if(!*iter) {
				continue;
			}
			clang::ParmVarDecl& parmVarDecl = **iter;
#endif
			dump(parmVarDecl, d+1, sourceManager, langOptions);
			QualType::dump(parmVarDecl.getType(), d+1, sourceManager, langOptions);
		}
		QualType::dump(funcDecl->getReturnType(), d+1, sourceManager, langOptions);

		break;
	}
	case clang::Decl::Kind::CXXMethod:
		break;
	case clang::Decl::Kind::CXXConstructor:
		break;
	case clang::Decl::Kind::CXXDestructor:
		break;
	case clang::Decl::Kind::CXXConversion:
		break;
	case clang::Decl::Kind::Var: {
		clang::VarDecl* varDecl = reinterpret_cast<clang::VarDecl*>(&decl);
		//auto varDecl = llvm::cast<clang::VarDecl>(&decl);

		//std::string varName = varDecl->getNameAsString();
		std::string varName = varDecl->getQualifiedNameAsString();
		std::string varType = varDecl->getType().getAsString();

		llvm::outs() << std::string(2*d, ' ') << "  Name:    '" << varName << "'\n";
		llvm::outs() << std::string(2*d, ' ') << "  Type:    '" << varType << "'\n";
		llvm::outs() << std::string(2*d, ' ') << "  Storage: ";
		if(varDecl->hasGlobalStorage()) {
			llvm::outs() << "global";
		}
		if(varDecl->hasLocalStorage()) {
			llvm::outs() << "local";
		}
		if(varDecl->hasExternalStorage()) {
			llvm::outs() << ", external";
		}
		llvm::outs() << "'\n";

		if(varDecl->hasInit()) {
			clang::Expr* expr = varDecl->getInit();
			if(expr) {
				Stmt::dump(*expr, d+1, sourceManager, langOptions);
			}
		}

		break;
	}
	case clang::Decl::Kind::VarTemplateSpecialization:
		break;
	case clang::Decl::Kind::VarTemplatePartialSpecialization:
		break;
	case clang::Decl::Kind::Decomposition:
		break;
	case clang::Decl::Kind::FunctionTemplate:
		break;
	case clang::Decl::Kind::ClassTemplate:
		break;
	case clang::Decl::Kind::TemplateTemplateParm:
		break;
	case clang::Decl::Kind::VarTemplate:
		break;
	case clang::Decl::Kind::Using:
		break;
	case clang::Decl::Kind::UsingShadow:
		break;
	case clang::Decl::Kind::ConstructorUsingShadow:
		break;
	case clang::Decl::Kind::ObjCMethod:
		break;
	case clang::Decl::Kind::ObjCCategory:
		break;
	case clang::Decl::Kind::ObjCProtocol:
		break;
	case clang::Decl::Kind::ObjCInterface:
		break;
	case clang::Decl::Kind::ObjCProperty:
		break;
	case clang::Decl::Kind::ObjCPropertyImpl:
		break;
	case clang::Decl::Kind::ObjCCompatibleAlias:
		break;
	case clang::Decl::Kind::Friend:
		break;
	case clang::Decl::Kind::FriendTemplate:
		break;
	}




	// Only walk declarations from our file.
	//if (sourceManager.isInMainFile(sourceManager.getSpellingLoc(decl.getBeginLoc()))) {
	if (sourceManager.isInMainFile(                             decl.getBeginLoc() )) {
		auto sourceRange = decl.getSourceRange();
		clang::SourceLocation sourceLocationBegin = sourceRange.getBegin();
		//sourceLocationBegin = sourceManager.getSpellingLoc(sourceRange.getBegin());
		//clang::PresumedLoc presumeSourceLocationBegin = sourceManager.getPresumedLoc(sourceLocationBegin);
		clang::SourceLocation sourceLocationEnd = sourceRange.getEnd();
		llvm::StringRef fileName = sourceManager.getFilename(sourceLocationBegin);

		unsigned int fileOffsetBegin = sourceManager.getFileOffset(sourceLocationBegin);
		auto fileOffsetEnd = sourceManager.getFileOffset(sourceLocationEnd);
		unsigned int lineNoBegin = sourceManager.getSpellingLineNumber(sourceLocationBegin);
		unsigned int colNoBegin = sourceManager.getSpellingColumnNumber(sourceLocationBegin);
		unsigned int lineNoEnd = sourceManager.getSpellingLineNumber(sourceLocationEnd);
		unsigned int colNoEnd = sourceManager.getSpellingColumnNumber(sourceLocationEnd);
		//clang::SourceLocation thisline=sourceManager.translateLineCol(sourceManager.getMainFileID(),17,1); // get the beginning of line 17
		//clang::SourceLocation nextline=sourceManager.translateLineCol(sourceManager.getMainFileID(),18,1); // get the beginning of line 18


#if 1
		llvm::StringRef str = clang::Lexer::getSourceText(clang::CharSourceRange::getTokenRange(sourceRange), sourceManager, langOptions);
#else
		clang::Rewriter rewriter;
		rewriter.setSourceMgr(sourceManager, astContext.getLangOpts());
		std::string str = rewriter.getRewrittenText(sourceRange);
#endif
		llvm::outs() << std::string(2*d, ' ') << "Source-Decl: <" << fileName << ", " << fileOffsetBegin << " [" << lineNoBegin << "," << colNoBegin << "], " << fileOffsetEnd << " [" << lineNoEnd << "," << colNoEnd << "]>\n";
		llvm::outs() << std::string(2*d, ' ') << "==== BEGIN ====\n";
		llvm::outs() << str << "\n";
		llvm::outs() << std::string(2*d, ' ') << "===== END =====\n";
	}


	clang::Stmt* stmt = decl.getBody();
	if(stmt) {
		Stmt::dump(*stmt, d+1, sourceManager, langOptions);
	}
}

} /* namespace myclang */
