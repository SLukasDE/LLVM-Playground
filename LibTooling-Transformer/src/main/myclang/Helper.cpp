#include "myclang/Helper.h"

#include <fstream>
/*
#include "clang/Tooling/Core/Replacement.h"

const clang::tooling::FormatStyle* Style;
clang::tooling::Lexer* Lex;
clang::tooling::SourceManager* SourceMgr;
clang::tooling::CharSourceRange* Ranges;

clang::tooling::Replacements reformat(const clang::tooling::FormatStyle &Style, clang::tooling::Lexer &Lex,
		clang::tooling::SourceManager &SourceMgr,
                               std::vector<clang::tooling::CharSourceRange> Ranges);
*/
namespace myclang {

std::vector<std::string> Helper::getSyntaxOnlyToolArgs(const std::vector<std::string>& extraArgs, llvm::StringRef fileName) {
	std::vector<std::string> args;

	args.push_back("transformer");
//	args.push_back("clang-tool");
	args.push_back("-fsyntax-only");

	args.insert(args.end(), extraArgs.begin(), extraArgs.end());
	args.push_back(fileName.str());

	return args;
}

bool Helper::customRunToolOnCodeWithArgs(std::unique_ptr<clang::FrontendAction> frontendAction, const llvm::Twine& code, const std::vector<std::string>& args, const llvm::Twine& fileName, const clang::tooling::FileContentMappings& virtualMappedFiles) {
	llvm::SmallString<16> fileNameStorage;
	llvm::StringRef fileNameRef = fileName.toNullTerminatedStringRef(fileNameStorage);

	llvm::IntrusiveRefCntPtr<clang::FileManager> files(new clang::FileManager(clang::FileSystemOptions()));
	auto pchContainer = std::make_shared<clang::PCHContainerOperations>();
	clang::tooling::ToolInvocation invocation(getSyntaxOnlyToolArgs(args, fileNameRef), std::move(frontendAction), files.get(), pchContainer);

	llvm::SmallString<1024> codeStorage;
	invocation.mapVirtualFile(fileNameRef, code.toNullTerminatedStringRef(codeStorage));

	for (auto &filenameWithContent : virtualMappedFiles) {
		invocation.mapVirtualFile(filenameWithContent.first, filenameWithContent.second);
	}

	return invocation.run();
}

bool Helper::fileExists(const std::string& file) {
	return std::ifstream(file).good();
}

std::vector<std::string> Helper::getCompileArgs(const std::vector<clang::tooling::CompileCommand>& compileCommands) {
	std::vector<std::string> compileArgs;

	for(const auto& cmd : compileCommands) {
		for(const auto& arg : cmd.CommandLine) {
			compileArgs.push_back(arg);
		}
	}

	if(compileArgs.empty() == false) {
		compileArgs.erase(begin(compileArgs));
		compileArgs.pop_back();
	}

	return compileArgs;
}

std::string Helper::getSourceCode(const std::string& sourceFile) {
	std::string sourcetxt = "";
	std::string temp = "";

	std::ifstream file(sourceFile);

	while(std::getline(file, temp)) {
		sourcetxt += temp + "\n";
	}

	return sourcetxt;
}

std::string Helper::getClangBuiltInIncludePath(const std::string& fullCallPath) {
	auto currentPath = fullCallPath;
	currentPath.erase(currentPath.rfind("/"));

	std::string line;
	std::ifstream file(currentPath + "/builtInInclude.path");
	std::getline(file, line);

	return line;
}

} /* namespace myclang */
