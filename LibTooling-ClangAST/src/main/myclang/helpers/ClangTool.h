#ifndef MYCLANG_HELPERS_CLANGTOOL_H_
#define MYCLANG_HELPERS_CLANGTOOL_H_

#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"

#include <memory>

namespace myclang {
namespace helpers {

class ClangTool {
public:
	ClangTool() = delete;

	static int run(int argc, const char **argv, clang::tooling::ToolAction& toolAction, bool debug);
};

} /* namespace helpers */
} /* namespace myclang */

#endif /* MYCLANG_HELPERS_CLANGTOOL_H_ */
