#include "myclang/astconsumers/ParsedTemplates.h"
#include "myclang/astfrontendactions/ParsedTemplates.h"

namespace myclang {
namespace astfrontendactions {

std::unique_ptr<clang::ASTConsumer> ParsedTemplates::CreateASTConsumer(clang::CompilerInstance& compilerInstance, llvm::StringRef) {
	auto module = getCurrentModule();
	if(module) {
		llvm::errs() << "Module:\n";
		llvm::errs() << "  Name: \"" << getCurrentModule()->Name << "\"\n";
	}
	else {
		llvm::errs() << "Module: (nullptr)\n";
	}
	//getActionType()

	return std::make_unique<astconsumers::ParsedTemplates>(compilerInstance, parsedTemplates);
}

bool ParsedTemplates::ParseArgs(const clang::CompilerInstance& compilerInstance, const std::vector<std::string>& args) {
	for (unsigned i = 0; i < args.size(); ++i) {
		llvm::errs() << "PrintFunctionNames arg = " << args[i] << "\n";

		// Example error handling.
		clang::DiagnosticsEngine& diagnosticsEngine = compilerInstance.getDiagnostics();
		if (args[i] == "-an-error") {
			unsigned diagID = diagnosticsEngine.getCustomDiagID(clang::DiagnosticsEngine::Error, "invalid argument '%0'");
			diagnosticsEngine.Report(diagID) << args[i];
			return false;
		} else if (args[i] == "-parse-template") {
			if (i + 1 >= args.size()) {
				diagnosticsEngine.Report(diagnosticsEngine.getCustomDiagID(clang::DiagnosticsEngine::Error, "missing -parse-template argument"));
				return false;
			}
			++i;
			parsedTemplates.insert(args[i]);
		}
	}

	if (!args.empty() && args[0] == "help") {
		printHelp(llvm::errs());
	}

    return true;
}

void ParsedTemplates::printHelp(llvm::raw_ostream& ros) {
	ros << "Help for PrintFunctionNames plugin goes here\n";
}

} /* namespace astfrontendactions */
} /* namespace myclang */
