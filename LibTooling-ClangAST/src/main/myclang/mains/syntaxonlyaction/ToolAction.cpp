#include "myclang/helpers/ClangTool.h"
#include "myclang/astfrontendactions/SyntaxOnlyAction.h"

#include "clang/Tooling/Tooling.h"

#include <memory>

int main(int argc, char const **argv) {
	std::unique_ptr<clang::tooling::ToolAction> toolAction = clang::tooling::newFrontendActionFactory<myclang::astfrontendactions::SyntaxOnlyAction>();
	return myclang::helpers::ClangTool::run(argc, argv, *toolAction, false);
}
