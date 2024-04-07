#include "myclang/helpers/ClangTool.h"

#include "clang/Tooling/CommonOptionsParser.h"

#include "llvm/Support/CommandLine.h"           // llvm::cl::OptionCategory, llvm::cl::extrahelp

#include <iostream>


static llvm::cl::OptionCategory optionCategory("my-tool options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static llvm::cl::extrahelp commonHelp(clang::tooling::CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static llvm::cl::extrahelp moreHelp("\nMore help text...\n");

namespace myclang {
namespace helpers {

int ClangTool::run(int argc, const char **argv, clang::tooling::ToolAction& toolAction, bool debug) {
	clang::tooling::CommonOptionsParser commonOptionsParser(argc, argv, optionCategory);

	clang::tooling::CompilationDatabase& compilationDatabase = commonOptionsParser.getCompilations();
	const std::vector<std::string>& sourcePathList = commonOptionsParser.getSourcePathList();

	if(debug) {
		std::cout << "Show compilation database\n";
		std::cout << "-------------------------\n";
		std::vector<std::string> files = compilationDatabase.getAllFiles();
		std::cout << "  Files: (" << files.size() << ")\n";
		for(const auto& file : files) {
			std::cout << "  - \"" << file << "\"\n";
		}
		std::vector<clang::tooling::CompileCommand> compileCommands = compilationDatabase.getAllCompileCommands();
		std::cout << "  Compile commands: (" << compileCommands.size() << ")\n";
		for(const auto& compileCommand : compileCommands) {
			std::cout << "  - Filename    \"" << compileCommand.Filename << "\"\n";
			std::cout << "    Directory   \"" << compileCommand.Directory << "\"\n";
			std::cout << "    Heuristic   \"" << compileCommand.Heuristic << "\"\n";
			std::cout << "    Output      \"" << compileCommand.Output << "\"\n";
			std::cout << "    CommandLine (" << compileCommand.CommandLine.size() << ")\n";
			for(std::size_t i = 0; i<compileCommand.CommandLine.size(); ++i) {
				std::cout << "      [" << i << "]: \"" << compileCommand.CommandLine[i] << "\"\n";
			}
		}
		std::cout << "\n";

		std::cout << "Show source path list\n";
		std::cout << "---------------------\n";
		for(const auto& sourcePath : sourcePathList) {
			std::cout << "- \"" << sourcePath << "\"\n";
		}
		std::cout << "---------------------\n";
	}

	clang::tooling::ClangTool clangTool(compilationDatabase, sourcePathList);

	return clangTool.run(&toolAction);
}

} /* namespace helpers */
} /* namespace myclang */
