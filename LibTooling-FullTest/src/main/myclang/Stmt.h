#ifndef MYCLANG_STMT_H_
#define MYCLANG_STMT_H_

#include "clang/Basic/SourceManager.h"
#include "clang/Basic/LangOptions.h"
#include "clang/AST/Stmt.h"

#include <string>

namespace myclang {

class Stmt final {
public:
	Stmt() = delete;

	static void dump(clang::Stmt& stmt, std::size_t d, clang::SourceManager& sourceManager, const clang::LangOptions& langOptions);
};

} /* namespace myclang */

#endif /* MYCLANG_STMT_H_ */
