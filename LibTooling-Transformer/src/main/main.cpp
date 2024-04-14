#include "myclang/Helper.h"
#include "myclang/Action.h"

#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/CompilationDatabase.h> // clang::tooling::CompileCommand

#include <llvm/Support/CommandLine.h>

#include <string>
#include <vector>

int main(int argc, const char **argv) {
	llvm::cl::OptionCategory ctCategory("transformer options");
	clang::tooling::CommonOptionsParser optionsParser(argc, argv, ctCategory);

	const std::vector<std::string>& sourcePathList = optionsParser.getSourcePathList();
	llvm::outs() << sourcePathList.size() << " files in source path list.\n";

	for(const std::string& sourceFile : sourcePathList) {
		if(myclang::Helper::fileExists(sourceFile) == false) {
			llvm::errs() << "File: " << sourceFile << " does not exist!\n";
			return -1;
		}

		llvm::outs() << "File to process: " << sourceFile << "\n";
		std::string sourcetxt = myclang::Helper::getSourceCode(sourceFile);

		std::vector<clang::tooling::CompileCommand> compileCommands = optionsParser.getCompilations().getCompileCommands(clang::tooling::getAbsolutePath(sourceFile));

		std::vector<std::string> compileArgs = myclang::Helper::getCompileArgs(compileCommands);
		llvm::outs() << "Get compile args: " << compileArgs.size() << "\n";

		//llvm::outs() << "Enrich compile args...\n";
		//compileArgs.push_back("-I" + myclang::Helper::getClangBuiltInIncludePath(argv[0]));

		llvm::outs() << "Compile args:\n";
		for(auto &s : compileArgs) {
			llvm::outs() << s << "\n";
		}

		auto myFrontendAction = std::make_unique<myclang::Action>();
		myclang::Helper::customRunToolOnCodeWithArgs(move(myFrontendAction), sourcetxt, compileArgs, sourceFile);
	}

	return 0;
}
