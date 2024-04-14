#include "myclang/helpers/CompilerInstance.h"

#include "clang/Basic/Diagnostic.h"                        // clang::DiagnosticsEngine
#include "clang/Basic/DiagnosticOptions.h"                 // clang::DiagnosticOptions
#include "clang/Basic/Builtins.h"                 // clang::Builtin::Context
#include "clang/Parse/ParseAST.h"                 // clang::ParseAST
#include "clang/Frontend/ASTUnit.h"                        // clang::ASTUnit
#include "clang/Sema/Sema.h"                               // clang::Sema
#include "clang/Serialization/PCHContainerOperations.h"    // clang::PCHContainerOperations

//#define MEM_BUFFER_FILE
#ifdef MEM_BUFFER_FILE
#include "llvm/Support/MemoryBuffer.h"
#endif

namespace myclang {
namespace helpers {

CompilerInstance::CompilerInstance(const std::string& inputFileStr) {
	compilerInstance.createDiagnostics(nullptr, true);



	// ...
	std::shared_ptr<clang::TargetOptions> to(new clang::TargetOptions);
	to->Triple = llvm::sys::getDefaultTargetTriple();
	clang::TargetInfo* ti = clang::TargetInfo::CreateTargetInfo(compilerInstance.getDiagnostics(), to);

	compilerInstance.setTarget(ti);

	// ...
	clang::LangOptions& langOptions = compilerInstance.getLangOpts();
	langOptions.GNUMode = 1;
	langOptions.CXXExceptions = 1;
	langOptions.RTTI = 1;
	langOptions.Bool = 1;   // <-- Note the Bool option here !
	langOptions.CPlusPlus = 1;
	clang::PreprocessorOptions& PPOpts = compilerInstance.getPreprocessorOpts();

	clang::InputKind IK(clang::Language::CXX);

	llvm::Triple triple;

	//clang::CompilerInvocation::setLangDefaults(langOptions, IK, triple, PPOpts, clang::LangStandard::lang_gnu11);
	clang::CompilerInvocation::setLangDefaults(langOptions, IK, triple, PPOpts, clang::LangStandard::lang_gnucxx20);
	// ...


	// ...
	compilerInstance.createFileManager();
	clang::FileManager& fileManager = compilerInstance.getFileManager();
	compilerInstance.createSourceManager(fileManager);
	clang::SourceManager& sourceManager = compilerInstance.getSourceManager();

	// ...
	clang::HeaderSearchOptions& hso = compilerInstance.getHeaderSearchOpts();

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



	// ...
	compilerInstance.createPreprocessor(clang::TranslationUnitKind::TU_Complete);
	clang::Preprocessor& preprocessor = compilerInstance.getPreprocessor();

	clang::Builtin::Context& bc = preprocessor.getBuiltinInfo();
#if 1
	clang::IdentifierTable& bcIdentifierTable = preprocessor.getIdentifierTable();
	const clang::LangOptions& bcLangOptions = preprocessor.getLangOpts();
	bc.initializeBuiltins(bcIdentifierTable, bcLangOptions);
#else
	bc.initializeBuiltins(preprocessor.getIdentifierTable(), preprocessor.getLangOpts());
#endif

	// ...

	compilerInstance.createASTContext();

#ifdef MEM_BUFFER_FILE
	std::unique_ptr<llvm::MemoryBuffer> memBuffer =	llvm::MemoryBuffer::getMemBuffer("StringRef InputData");
	clang::FileID fileId = sourceManager.createFileID(std::move(memBuffer));
#else
	llvm::ErrorOr<const clang::FileEntry *> inputFile = fileManager.getFile(inputFileStr);
	clang::FileID fileId = sourceManager.createFileID(inputFile.get(), clang::SourceLocation(), clang::SrcMgr::C_User);
#endif
	sourceManager.setMainFileID(fileId);

	compilerInstance.getDiagnosticClient().BeginSourceFile(compilerInstance.getLangOpts(), &compilerInstance.getPreprocessor());


}

clang::ASTContext& CompilerInstance::getASTContext() {
	return compilerInstance.getASTContext();
}

clang::CompilerInstance& CompilerInstance::getCompilerInstance() {
	return compilerInstance;
}

void CompilerInstance::run(clang::ASTConsumer& astConsumer) {
	// ...
	clang::ParseAST(compilerInstance.getPreprocessor(), &astConsumer, compilerInstance.getASTContext(), false, clang::TranslationUnitKind::TU_Complete, nullptr, false);
	// ...

}

} /* namespace helpers */
} /* namespace myclang */
