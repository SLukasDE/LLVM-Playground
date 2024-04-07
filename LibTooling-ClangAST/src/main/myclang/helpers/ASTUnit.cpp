#include "myclang/helpers/ASTUnit.h"

#include "clang/Basic/Diagnostic.h"                        // clang::DiagnosticsEngine
#include "clang/Basic/DiagnosticOptions.h"                 // clang::DiagnosticOptions
#include "clang/Frontend/CompilerInstance.h"               // clang::CompilerInstance
#include "clang/Serialization/PCHContainerOperations.h"    // clang::PCHContainerOperations

#include <stdexcept>

namespace myclang {
namespace helpers {

ASTUnit::ASTUnit(int argc, char const **argv) {
	// Point 'LoadFromCommandLine' at the clang binary so it will be able
	// to find its compiler headers such as stddef.h.
	argv[0] = "/usr" /*CLANG_LLVM_INSTALL_DIR*/ "/bin/clang";

	// Boilerplate setup for 'LoadFromCommandLine'.
	std::shared_ptr<clang::PCHContainerOperations> pchContainerOps(new clang::PCHContainerOperations());
	clang::IntrusiveRefCntPtr<clang::DiagnosticsEngine> diagnosticsEngine(
			clang::CompilerInstance::createDiagnostics(new clang::DiagnosticOptions));

	// Run the Clang parser to produce an AST.
	astUnit.reset(clang::ASTUnit::LoadFromCommandLine(
		argv,
		argv + argc,
		pchContainerOps,
		diagnosticsEngine,
		llvm::StringRef() /*ResourceFilesPath, evidently ignored*/));

	if(!astUnit || diagnosticsEngine->hasErrorOccurred()) {
		throw std::runtime_error("Cannot create ASTUnit");
	}
}

clang::ASTUnit& ASTUnit::getASTUnit() {
	return *astUnit;
}

} /* namespace helpers */
} /* namespace myclang */
