#include "myclang/Main.h"
#include "myclang/CompilerInstance.h"
#include "myclang/Decl.h"
#include "myclang/QualType.h"
#include "myclang/Stmt.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclObjC.h"
#include "clang/AST/DeclTemplate.h"
#include "clang/AST/TemplateName.h"
#include "clang/AST/Type.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h" // clang::SyntaxOnlyAction
#include "clang/Parse/ParseAST.h"                          // clang::ParseAST(...)
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Sema/ExternalSemaSource.h"
#include "clang/Sema/Lookup.h"
#include "clang/Sema/Ownership.h"
#include "clang/Sema/Sema.h"
#include "clang/Sema/SemaConsumer.h"
#include "clang/Tooling/JSONCompilationDatabase.h"
#include "clang/Tooling/Tooling.h"

#include "llvm/Support/raw_ostream.h"                      // llvm::raw_ostream


#include <iostream>
#include <memory>

namespace myclang {

Main::Main() {
}

int Main::run(const std::string& filename) {
	CompilerInstance compilerInstance(true);

#if 0
	std::string sourceCode = "struct X { int i; };";
	compilerInstance.setSourceCode(sourceCode);
#else
	compilerInstance.setSourceFile(filename);
#endif
	//compilerInstance.getASTContext();

#if 1
	struct X : clang::SyntaxOnlyAction {
		std::unique_ptr<clang::ASTConsumer> createASTConsumer(CompilerInstance& compilerInstance) {
			return CreateASTConsumer(compilerInstance, "");
		}
	} action;
	std::unique_ptr<clang::ASTConsumer> consumer = action.createASTConsumer(compilerInstance);
#endif

#if 0
	llvm::StringRef filter = compilerInstance.getFrontendOpts().ASTDumpFilter;
	auto outputStream = compilerInstance.createDefaultOutputFile(false);
	if(!outputStream) {
		llvm::outs() << "No output stream available\n";
		return 0;
	}
	std::unique_ptr<clang::ASTConsumer> consumer = clang::CreateASTPrinter(std::move(outputStream), filter);
#endif

#if 0
	std::unique_ptr<clang::ASTConsumer> consumer = clang::CreateASTDumper(
			nullptr,            /* dump to stdout */
			"",                 /* no filter */
			true,               /* dump decls */
			true,               /* deserialize */
			false,              /* don't dump lookups */
			clang::ADOF_Default /* default instead of json */
			);
#endif


	class DynamicIDHandler : public clang::ExternalSemaSource {
	public:
		DynamicIDHandler(clang::Sema& aSema)
		: sema(aSema),
		astContext(sema.getASTContext())
		{}

		~DynamicIDHandler() = default;

		/// \brief Provides last resort lookup for failed unqualified lookups
		///
		/// If there is failed lookup, tell sema to create an artificial declaration
		/// which is of dependent type. So the lookup result is marked as dependent
		/// and the diagnostics are suppressed. After that is's an interpreter's
		/// responsibility to fix all these fake declarations and lookups.
		/// It is done by the DynamicExprTransformer.
		///
		/// @param[out] R The recovered symbol.
		/// @param[in] S The scope in which the lookup failed.
		bool LookupUnqualified(clang::LookupResult &R, clang::Scope *S) override {
			clang::DeclarationName Name = R.getLookupName();
			llvm::outs() << Name.getAsString() << "\n";
			// IdentifierInfo *II = Name.getAsIdentifierInfo();
			// SourceLocation Loc = R.getNameLoc();
			// VarDecl *Result =
			//     // VarDecl::Create(astContext, R.getSema().getFunctionLevelDeclContext(),
			//     //                 Loc, Loc, II, astContext.DependentTy,
			//     //                 /*TypeSourceInfo*/ 0, SC_None, SC_None);
			// if (Result) {
			//   R.addDecl(Result);
			//   // Say that we can handle the situation. Clang should try to recover
			//   return true;
			// } else{
			//   return false;
			// }
			return false;
		}

	private:
		clang::Sema& sema;
		clang::ASTContext& astContext;
	};

	llvm::outs() << "BEFORE PARSE\n";
#if 1
	compilerInstance.createSema(clang::TranslationUnitKind::TU_Complete, nullptr);
	clang::Sema& sema = compilerInstance.getSema();
	sema.Initialize();
	DynamicIDHandler externalSemaSource(sema);
	sema.addExternalSource(&externalSemaSource);

	compilerInstance.getDiagnosticClient().BeginSourceFile(compilerInstance.getLangOpts(), &compilerInstance.getPreprocessor());
	clang::ParseAST(sema, true, false);
    compilerInstance.getDiagnosticClient().EndSourceFile();
#else
	clang::ParseAST(compilerInstance.getPreprocessor(), consumer.get(), compilerInstance.getASTContext(), false, clang::TranslationUnitKind::TU_Complete, nullptr, false);
#endif
	llvm::outs() << "AFTER PARSE\n";

	clang::ASTContext& astContext = compilerInstance.getASTContext();
	clang::TranslationUnitDecl* translationUnitDecl = astContext.getTranslationUnitDecl();
	if(translationUnitDecl) {
		clang::SourceManager& sourceManager = astContext.getSourceManager();
		const clang::LangOptions& langOptions = astContext.getLangOpts();

		//clang::DeclContext::decl_range x = translationUnitDecl->decls();
		//for(auto declaration : translationUnitDecl->decls())
		for(clang::DeclContext::decl_iterator iter = translationUnitDecl->decls_begin(); iter != translationUnitDecl->decls_end(); ++iter) {
			clang::Decl& decl = **iter;

			Decl::dump(decl, 0, sourceManager, langOptions);
		}
	}

	return 0;
}

} /* namespace myclang */
