#include "myclang/helpers/ClangTool.h"
#include "myclang/ast_matchers/MatchDecls.h"

#include "clang/Tooling/Tooling.h"

int main(int argc, char const **argv) {
	myclang::ast_matchers::MatchDecls matchFinder(true);
	clang::tooling::ToolAction& toolAction = matchFinder.getToolAction();

	return myclang::helpers::ClangTool::run(argc, argv, toolAction, false);
}
