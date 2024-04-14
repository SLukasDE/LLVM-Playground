#include "myclang/Decl.h"
#include "myclang/Stmt.h"

#include "clang/AST/Decl.h"
#include "clang/AST/DeclObjC.h"
#include "clang/AST/Expr.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Lex/Lexer.h"

#include "llvm/ADT/StringRef.h"                            // llvm::StringRef
#include "llvm/Support/Casting.h"
#include "llvm/Support/raw_ostream.h"                      // llvm::raw_ostream

namespace myclang {

void Stmt::dump(clang::Stmt& stmt, std::size_t d, clang::SourceManager& sourceManager, const clang::LangOptions& langOptions) {
	llvm::outs() << std::string(2*d, ' ') << "\n";
	llvm::outs() << std::string(2*d, ' ') << "DUMP-STMT\n";
	llvm::outs() << std::string(2*d, ' ') << "---------\n";

	llvm::outs() << std::string(2*d, ' ') << "StmtClass: '" << stmt.getStmtClassName() << "'\n";

	clang::Stmt::StmtClass stmtClass = stmt.getStmtClass();
	switch(stmtClass) {
	case clang::Stmt::NoStmtClass:
	case clang::Stmt::CaseStmtClass:
	case clang::Stmt::DefaultStmtClass:
	case clang::Stmt::IfStmtClass:
	case clang::Stmt::SwitchStmtClass:
	case clang::Stmt::WhileStmtClass:
	case clang::Stmt::DoStmtClass:
	case clang::Stmt::ForStmtClass:
	case clang::Stmt::GotoStmtClass:
	case clang::Stmt::IndirectGotoStmtClass:
	case clang::Stmt::ContinueStmtClass:
	case clang::Stmt::BreakStmtClass:
	case clang::Stmt::ReturnStmtClass:
	case clang::Stmt::GCCAsmStmtClass:
	case clang::Stmt::MSAsmStmtClass:
	case clang::Stmt::ObjCAtTryStmtClass:
	case clang::Stmt::ObjCAtCatchStmtClass:
	case clang::Stmt::ObjCAtFinallyStmtClass:
	case clang::Stmt::ObjCAtThrowStmtClass:
	case clang::Stmt::ObjCAtSynchronizedStmtClass:
	case clang::Stmt::ObjCAutoreleasePoolStmtClass:
	case clang::Stmt::ObjCForCollectionStmtClass:
	case clang::Stmt::CXXCatchStmtClass:
	case clang::Stmt::CXXTryStmtClass:
	case clang::Stmt::CXXForRangeStmtClass:
	case clang::Stmt::SEHTryStmtClass:
	case clang::Stmt::SEHExceptStmtClass:
	case clang::Stmt::SEHFinallyStmtClass:
	case clang::Stmt::SEHLeaveStmtClass:
	case clang::Stmt::CoroutineBodyStmtClass:
	case clang::Stmt::CoreturnStmtClass:
	case clang::Stmt::ArrayTypeTraitExprClass:
	case clang::Stmt::AsTypeExprClass:
	case clang::Stmt::AtomicExprClass:
	case clang::Stmt::BinaryConditionalOperatorClass:
	case clang::Stmt::TypeTraitExprClass:
	case clang::Stmt::CoawaitExprClass:
	case clang::Stmt::DependentCoawaitExprClass:
	case clang::Stmt::CoyieldExprClass:
	case clang::Stmt::CXXBindTemporaryExprClass:
	case clang::Stmt::CXXDefaultArgExprClass:
	case clang::Stmt::CXXDefaultInitExprClass:
	case clang::Stmt::CXXFoldExprClass:
	case clang::Stmt::CXXRewrittenBinaryOperatorClass:
	case clang::Stmt::CXXStdInitializerListExprClass:
	case clang::Stmt::CXXScalarValueInitExprClass:
	case clang::Stmt::CXXUuidofExprClass:
	case clang::Stmt::ChooseExprClass:
	case clang::Stmt::DesignatedInitExprClass:
	case clang::Stmt::DesignatedInitUpdateExprClass:
	case clang::Stmt::ArrayInitLoopExprClass:
	case clang::Stmt::ArrayInitIndexExprClass:
	case clang::Stmt::ExprWithCleanupsClass:
	case clang::Stmt::ExpressionTraitExprClass:
	case clang::Stmt::ExtVectorElementExprClass:
	case clang::Stmt::ImplicitCastExprClass:
	case clang::Stmt::ImplicitValueInitExprClass:
	case clang::Stmt::NoInitExprClass:
	case clang::Stmt::MaterializeTemporaryExprClass:
	case clang::Stmt::ObjCIndirectCopyRestoreExprClass:
	case clang::Stmt::OffsetOfExprClass:
	case clang::Stmt::ParenListExprClass:
	case clang::Stmt::PredefinedExprClass:
	case clang::Stmt::ShuffleVectorExprClass:
	case clang::Stmt::SourceLocExprClass:
	case clang::Stmt::ConvertVectorExprClass:
	case clang::Stmt::VAArgExprClass:
	case clang::Stmt::ObjCArrayLiteralClass:
	case clang::Stmt::ObjCDictionaryLiteralClass:
	case clang::Stmt::ObjCBoxedExprClass:
	case clang::Stmt::ObjCSubscriptRefExprClass:
		break;
	case clang::Stmt::OpaqueValueExprClass: {
		clang::Expr* src = llvm::cast<clang::OpaqueValueExpr>(&stmt)->getSourceExpr();
		break;
	}
	case clang::Stmt::PseudoObjectExprClass: {
		clang::Expr* src = llvm::cast<clang::PseudoObjectExpr>(&stmt)->getSyntacticForm();
		break;
	}
	case clang::Stmt::CompoundStmtClass: {
		//clang::Expr* src = llvm::cast<clang::PseudoObjectExpr>(&stmt)->getSyntacticForm();
		llvm::outs() << std::string(2*d, ' ') << "{ #### BLOCK #### }\n";
		break;
	}
	case clang::Stmt::NullStmtClass:
	case clang::Stmt::LabelStmtClass:
	case clang::Stmt::AttributedStmtClass:
	case clang::Stmt::DeclStmtClass:
	case clang::Stmt::CapturedStmtClass:
	case clang::Stmt::IntegerLiteralClass:
	case clang::Stmt::FixedPointLiteralClass:
	case clang::Stmt::FloatingLiteralClass:
	case clang::Stmt::ImaginaryLiteralClass:
	case clang::Stmt::StringLiteralClass:
	case clang::Stmt::CharacterLiteralClass:
		break;
	case clang::Stmt::ConstantExprClass: {
		clang::Expr* src = llvm::cast<clang::ConstantExpr>(&stmt)->getSubExpr();
		break;
	}
	case clang::Stmt::ParenExprClass:
	case clang::Stmt::UnaryOperatorClass:
	case clang::Stmt::UnaryExprOrTypeTraitExprClass:
	case clang::Stmt::CXXNoexceptExprClass:
	case clang::Stmt::MSPropertySubscriptExprClass:
	case clang::Stmt::ArraySubscriptExprClass:
	case clang::Stmt::OMPArraySectionExprClass:
	case clang::Stmt::BinaryOperatorClass:
	case clang::Stmt::CompoundAssignOperatorClass:
	case clang::Stmt::ConditionalOperatorClass:
	case clang::Stmt::CStyleCastExprClass:
	case clang::Stmt::CompoundLiteralExprClass:
	case clang::Stmt::InitListExprClass:
	case clang::Stmt::AddrLabelExprClass:
	case clang::Stmt::StmtExprClass:
	case clang::Stmt::GenericSelectionExprClass:
	case clang::Stmt::GNUNullExprClass:
	case clang::Stmt::CXXStaticCastExprClass:
	case clang::Stmt::CXXDynamicCastExprClass:
	case clang::Stmt::CXXReinterpretCastExprClass:
	case clang::Stmt::CXXConstCastExprClass:
	case clang::Stmt::CXXFunctionalCastExprClass:
	case clang::Stmt::CXXTypeidExprClass:
	case clang::Stmt::CXXBoolLiteralExprClass:
	case clang::Stmt::CXXNullPtrLiteralExprClass:
	case clang::Stmt::CXXThisExprClass:
	case clang::Stmt::CXXThrowExprClass:
	case clang::Stmt::CXXNewExprClass:
	case clang::Stmt::CXXDeleteExprClass:
	case clang::Stmt::ObjCStringLiteralClass:
	case clang::Stmt::ObjCEncodeExprClass:
	case clang::Stmt::ObjCSelectorExprClass:
	case clang::Stmt::ObjCProtocolExprClass:
	case clang::Stmt::ObjCBoolLiteralExprClass:
	case clang::Stmt::ObjCAvailabilityCheckExprClass:
	case clang::Stmt::ObjCBridgedCastExprClass:
	case clang::Stmt::BlockExprClass:
	case clang::Stmt::PackExpansionExprClass:
	case clang::Stmt::SizeOfPackExprClass:
		break;
	case clang::Stmt::DeclRefExprClass: {
		if (const clang::ImplicitParamDecl *IPD = llvm::dyn_cast_or_null<clang::ImplicitParamDecl>(llvm::cast<clang::DeclRefExpr>(&stmt)->getDecl())) {
			if (const clang::ObjCMethodDecl* MD = llvm::dyn_cast<clang::ObjCMethodDecl>(IPD->getDeclContext())) {
				if (MD->getSelfDecl() == IPD) {
					break;
				}
			}
		}
		break;
	}
	case clang::Stmt::DependentScopeDeclRefExprClass:
	case clang::Stmt::SubstNonTypeTemplateParmExprClass:
	case clang::Stmt::SubstNonTypeTemplateParmPackExprClass:
	case clang::Stmt::FunctionParmPackExprClass:
	case clang::Stmt::UnresolvedLookupExprClass:
	case clang::Stmt::TypoExprClass: // A typo could actually be a DeclRef or a MemberRef
	case clang::Stmt::CXXDependentScopeMemberExprClass:
	case clang::Stmt::CXXPseudoDestructorExprClass:
	case clang::Stmt::MemberExprClass:
	case clang::Stmt::MSPropertyRefExprClass:
	case clang::Stmt::ObjCIsaExprClass:
	case clang::Stmt::ObjCIvarRefExprClass:
	case clang::Stmt::ObjCPropertyRefExprClass:
	case clang::Stmt::UnresolvedMemberExprClass:
	case clang::Stmt::CallExprClass:
	case clang::Stmt::CXXOperatorCallExprClass:
	case clang::Stmt::CXXMemberCallExprClass:
	case clang::Stmt::CUDAKernelCallExprClass:
	case clang::Stmt::CXXConstructExprClass:
	case clang::Stmt::CXXInheritedCtorInitExprClass:
	case clang::Stmt::CXXTemporaryObjectExprClass:
	case clang::Stmt::CXXUnresolvedConstructExprClass:
	case clang::Stmt::UserDefinedLiteralClass:
	case clang::Stmt::LambdaExprClass:
	case clang::Stmt::ObjCMessageExprClass:
	case clang::Stmt::ConceptSpecializationExprClass:
	case clang::Stmt::RequiresExprClass:
	case clang::Stmt::MSDependentExistsStmtClass:
	case clang::Stmt::OMPParallelDirectiveClass:
	case clang::Stmt::OMPSimdDirectiveClass:
	case clang::Stmt::OMPForDirectiveClass:
	case clang::Stmt::OMPForSimdDirectiveClass:
	case clang::Stmt::OMPSectionsDirectiveClass:
	case clang::Stmt::OMPSectionDirectiveClass:
	case clang::Stmt::OMPSingleDirectiveClass:
	case clang::Stmt::OMPMasterDirectiveClass:
	case clang::Stmt::OMPCriticalDirectiveClass:
	case clang::Stmt::OMPParallelForDirectiveClass:
	case clang::Stmt::OMPParallelForSimdDirectiveClass:
	case clang::Stmt::OMPParallelMasterDirectiveClass:
	case clang::Stmt::OMPParallelSectionsDirectiveClass:
	case clang::Stmt::OMPTaskDirectiveClass:
	case clang::Stmt::OMPTaskyieldDirectiveClass:
	case clang::Stmt::OMPBarrierDirectiveClass:
	case clang::Stmt::OMPTaskwaitDirectiveClass:
	case clang::Stmt::OMPTaskgroupDirectiveClass:
	case clang::Stmt::OMPFlushDirectiveClass:
	case clang::Stmt::OMPOrderedDirectiveClass:
	case clang::Stmt::OMPAtomicDirectiveClass:
	case clang::Stmt::OMPTargetDirectiveClass:
	case clang::Stmt::OMPTargetDataDirectiveClass:
	case clang::Stmt::OMPTargetEnterDataDirectiveClass:
	case clang::Stmt::OMPTargetExitDataDirectiveClass:
	case clang::Stmt::OMPTargetParallelDirectiveClass:
	case clang::Stmt::OMPTargetParallelForDirectiveClass:
	case clang::Stmt::OMPTargetUpdateDirectiveClass:
	case clang::Stmt::OMPTeamsDirectiveClass:
	case clang::Stmt::OMPCancellationPointDirectiveClass:
	case clang::Stmt::OMPCancelDirectiveClass:
	case clang::Stmt::OMPTaskLoopDirectiveClass:
	case clang::Stmt::OMPTaskLoopSimdDirectiveClass:
	case clang::Stmt::OMPMasterTaskLoopDirectiveClass:
	case clang::Stmt::OMPMasterTaskLoopSimdDirectiveClass:
	case clang::Stmt::OMPParallelMasterTaskLoopDirectiveClass:
	case clang::Stmt::OMPParallelMasterTaskLoopSimdDirectiveClass:
	case clang::Stmt::OMPDistributeDirectiveClass:
	case clang::Stmt::OMPDistributeParallelForDirectiveClass:
	case clang::Stmt::OMPDistributeParallelForSimdDirectiveClass:
	case clang::Stmt::OMPDistributeSimdDirectiveClass:
	case clang::Stmt::OMPTargetParallelForSimdDirectiveClass:
	case clang::Stmt::OMPTargetSimdDirectiveClass:
	case clang::Stmt::OMPTeamsDistributeDirectiveClass:
	case clang::Stmt::OMPTeamsDistributeSimdDirectiveClass:
	case clang::Stmt::OMPTeamsDistributeParallelForSimdDirectiveClass:
	case clang::Stmt::OMPTeamsDistributeParallelForDirectiveClass:
	case clang::Stmt::OMPTargetTeamsDirectiveClass:
	case clang::Stmt::OMPTargetTeamsDistributeDirectiveClass:
	case clang::Stmt::OMPTargetTeamsDistributeParallelForDirectiveClass:
	case clang::Stmt::OMPTargetTeamsDistributeParallelForSimdDirectiveClass:
	case clang::Stmt::OMPTargetTeamsDistributeSimdDirectiveClass:
	case clang::Stmt::BuiltinBitCastExprClass:
		break;
	}
	if (clang::CallExpr* call = llvm::dyn_cast<clang::CallExpr>(&stmt)) {
		clang::FunctionDecl* funcDecl = call->getDirectCallee();
		if(funcDecl) {
			std::string funcCall = funcDecl->getNameInfo().getName().getAsString();
			llvm::outs() << std::string(2*d, ' ') << "Found function call '" << funcCall << "' with " << call->getNumArgs() << " arguments\n";
			Decl::dump(*funcDecl, d+1, sourceManager, langOptions);
		} else {
			std::string funcCall = funcDecl->getNameInfo().getName().getAsString();
			llvm::outs() << std::string(2*d, ' ') << "Found function call '(unknown)' with " << call->getNumArgs() << " arguments\n";
		}
	}



	auto sourceRangeBody = stmt.getSourceRange();
	unsigned int fileOffsetBegin = sourceManager.getFileOffset(sourceRangeBody.getBegin());
	auto fileOffsetEnd = sourceManager.getFileOffset(sourceRangeBody.getEnd());
	unsigned int lineNoBegin = sourceManager.getSpellingLineNumber(sourceRangeBody.getBegin());
	unsigned int colNoBegin = sourceManager.getSpellingColumnNumber(sourceRangeBody.getBegin());
	unsigned int lineNoEnd = sourceManager.getSpellingLineNumber(sourceRangeBody.getEnd());
	unsigned int colNoEnd = sourceManager.getSpellingColumnNumber(sourceRangeBody.getEnd());
	llvm::StringRef fileName = sourceManager.getFilename(sourceRangeBody.getBegin());

	llvm::StringRef str = clang::Lexer::getSourceText(clang::CharSourceRange::getTokenRange(sourceRangeBody), sourceManager, langOptions);
	llvm::outs() << std::string(2*d, ' ') << "Source-Stmt: <" << fileName << ", " << fileOffsetBegin << " [" << lineNoBegin << "," << colNoBegin << "], " << fileOffsetEnd << " [" << lineNoEnd << "," << colNoEnd << "]>\n";
	llvm::outs() << std::string(2*d, ' ') << "==== BEGIN ====\n";
	llvm::outs() << str << "\n";
	llvm::outs() << std::string(2*d, ' ') << "===== END =====\n";
}

} /* namespace myclang */
