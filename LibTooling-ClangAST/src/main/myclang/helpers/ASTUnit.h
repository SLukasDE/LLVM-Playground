#ifndef MYCLANG_HELPERS_ASTUNIT_H_
#define MYCLANG_HELPERS_ASTUNIT_H_

#include "clang/Frontend/ASTUnit.h"                        // clang::ASTUnit

#include <memory>

namespace myclang {
namespace helpers {

class ASTUnit {
public:
	ASTUnit(int argc, char const **argv);

	clang::ASTUnit& getASTUnit();

	template<typename Visitor>
	bool run(Visitor& visitor) {
		return visitor.TraverseDecl(astUnit->getASTContext().getTranslationUnitDecl());
	}

private:
	std::unique_ptr<clang::ASTUnit> astUnit;
};

} /* namespace helpers */
} /* namespace myclang */

#endif /* MYCLANG_HELPERS_ASTUNIT_H_ */
