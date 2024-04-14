#include "myclang/CompilerInstance.h"


#include "clang/Basic/Builtins.h"                          // clang::Builtin::Context
#include "clang/Basic/Diagnostic.h"                        // clang::DiagnosticsEngine
#include "clang/Basic/DiagnosticOptions.h"                 // clang::DiagnosticOptions
#include "clang/Basic/TargetInfo.h"                        // clang::TargetInfo
#include "clang/Basic/TargetOptions.h"                     // clang::TargetOptions
//#include "clang/Frontend/ASTUnit.h"                        // clang::ASTUnit
#include "clang/Lex/Preprocessor.h"                        // clang::Preprocessor
#include "clang/Lex/PreprocessorOptions.h"                 // clang::PreprocessorOptions
#include "clang/Parse/ParseAST.h"                          // clang::ParseAST(...)
#include "clang/Sema/Sema.h"                               // clang::Sema
#include "clang/Serialization/PCHContainerOperations.h"    // clang::PCHContainerOperations

#include "llvm/Support/MemoryBuffer.h"

#include <memory>

namespace myclang {

CompilerInstance::CompilerInstance(bool isCplusplus) {
	createDiagnostics();
	//createDiagnostics(nullptr, true);
	//clang::DiagnosticOptions diagnosticOptions;
	//createDiagnostics(&diagnosticOptions, nullptr, true, nullptr);

	{
		std::shared_ptr<clang::TargetOptions> targetOptions(new clang::TargetOptions);
		targetOptions->Triple = llvm::sys::getDefaultTargetTriple();
		clang::TargetInfo* targetInfo = clang::TargetInfo::CreateTargetInfo(getDiagnostics(), targetOptions);
		setTarget(targetInfo);
	}

	if(isCplusplus) {
		clang::LangOptions& langOptions = getLangOpts();
		langOptions.GNUMode = 1;
		langOptions.CXXExceptions = 1;
		langOptions.RTTI = 1;
		langOptions.Bool = 1;   // <-- Note the Bool option here !
		langOptions.CPlusPlus = 1;

		clang::PreprocessorOptions& preprocessorOptions = getPreprocessorOpts();
		clang::InputKind inputKind(clang::Language::CXX);
		llvm::Triple triple;

		//clang::CompilerInvocation::setLangDefaults(langOptions, inputKind, triple, preprocessorOptions, clang::LangStandard::lang_gnu11);
		clang::CompilerInvocation::setLangDefaults(langOptions, inputKind, triple, preprocessorOptions, clang::LangStandard::lang_gnucxx20);
	}


	createFileManager();
	clang::FileManager& fileManager = getFileManager();
	createSourceManager(fileManager);

	if(isCplusplus) {
		clang::HeaderSearchOptions& hso = getHeaderSearchOpts();

		//llvm::StringRef dir("/usr/lib/llvm-10/include");
		//hso.AddPath(dir, clang::frontend::Angled, false, false);

		llvm::StringRef dir1("/usr/include/c++/9");
		hso.AddPath(dir1, clang::frontend::Angled, false, false);

		llvm::StringRef dir2("/usr/include/x86_64-linux-gnu/c++/9");
		hso.AddPath(dir2, clang::frontend::Angled, false, false);

		llvm::StringRef dir3("/usr/include/x86_64-linux-gnu");
		hso.AddPath(dir3, clang::frontend::Angled, false, false);

		llvm::StringRef dir4("/usr/include");
		hso.AddPath(dir4, clang::frontend::Angled, false, false);

		//llvm::StringRef dir5("/usr/include/linux");
		llvm::StringRef dir5("/usr/lib/llvm-10/lib/clang/10.0.0/include");
		hso.AddPath(dir5, clang::frontend::Angled, false, false);

		// <clang build folder>/Release+Asserts/lib/clang/<clang version>
		//hso.ResourceDir = "/usr/lib/llvm-10/lib/clang/10.0.0";
	}

	createPreprocessor(clang::TranslationUnitKind::TU_Complete);

	clang::PreprocessorOptions& preprocessorOptions = getPreprocessorOpts();
	preprocessorOptions.UsePredefines = false;

	if(isCplusplus) {
		clang::Preprocessor& preprocessor = getPreprocessor();
		clang::Builtin::Context& builtinContext = preprocessor.getBuiltinInfo();
		clang::IdentifierTable& identifierTable = preprocessor.getIdentifierTable();
		const clang::LangOptions& langOptions = preprocessor.getLangOpts();
		builtinContext.initializeBuiltins(identifierTable, langOptions);
	}

	createASTContext();
}

void CompilerInstance::setSourceCode(const std::string& sourceCode) {
	clang::SourceManager& sourceManager = getSourceManager();

	std::unique_ptr<llvm::MemoryBuffer> memBuffer =	llvm::MemoryBuffer::getMemBuffer(sourceCode);
	clang::FileID fileId = sourceManager.createFileID(std::move(memBuffer));
	sourceManager.setMainFileID(fileId);

	getDiagnosticClient().BeginSourceFile(getLangOpts(), &getPreprocessor());
}

void CompilerInstance::setSourceFile(const std::string& sourceFile) {
	clang::SourceManager& sourceManager = getSourceManager();
	clang::FileManager& fileManager = getFileManager();

	llvm::ErrorOr<const clang::FileEntry *> inputFile = fileManager.getFile(sourceFile);
	//if (!inputFile) {
	//	std::cerr << "File not found: " << sourceFile << std::endl;
	//	return false;
	//}
	clang::FileID fileId = sourceManager.createFileID(inputFile.get(), clang::SourceLocation(), clang::SrcMgr::C_User);
	sourceManager.setMainFileID(fileId);

	getDiagnosticClient().BeginSourceFile(getLangOpts(), &getPreprocessor());
}
#if 0
void CompilerInstance::run1(clang::ASTConsumer& astConsumer) {
	clang::ParseAST(getPreprocessor(), &astConsumer, getASTContext(), false, clang::TranslationUnitKind::TU_Complete, nullptr, false);
}

void CompilerInstance::run2(clang::ASTConsumer& astConsumer) {
	getDiagnosticClient().BeginSourceFile(getLangOpts(), &getPreprocessor());
	run1(astConsumer);
	getDiagnosticClient().EndSourceFile();

}
#endif

} /* namespace myclang */
