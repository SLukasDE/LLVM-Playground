#ifndef MYCLANG_ASTVISITORS_CLASSSOURCE_H_
#define MYCLANG_ASTVISITORS_CLASSSOURCE_H_

#include "clang/AST/ASTContext.h"                          // clang::ASTContext
#include "clang/AST/DeclCXX.h"                             // clang::CXXRecordDecl
#include "clang/AST/DeclBase.h"                            // clang::DeclBase
#include "clang/AST/Type.h"                                // clang::QualType
#include "clang/AST/RecursiveASTVisitor.h"                 // clang::RecursiveASTVisitor
#include "clang/Frontend/ASTUnit.h"                        // clang::ASTUnit

namespace myclang {
namespace astvisitors {

class ClassSource : public clang::RecursiveASTVisitor<ClassSource> {
public:
	ClassSource(clang::ASTUnit& astUnit);

	// Kick off the traversal.
	//void myTraverseTU();

	// By default, AST visitors skip implicit nodes even if they are
	// present in the AST.  Returning true here ensures we will not skip
	// them.
	bool shouldVisitImplicitCode() { return true; }

	// Visitor methods.
	bool VisitCXXRecordDecl(clang::CXXRecordDecl* recordDecl);
	bool VisitCXXConstructorDecl(clang::CXXConstructorDecl* methodDecl);
	//bool VisitFunctionDecl(clang::FunctionDecl* functionDecl);


/*
  bool TraverseDecl(Decl *D);
  bool VisitDecl(Decl *D);
  // TranslationUnitDecl empty
  bool VisitNamedDecl(NamedDecl *D);
  bool VisitNamespaceDecl(NamespaceDecl *D);
  bool VisitUsingDirectiveDecl(UsingDirectiveDecl *D);
  bool VisitNamespaceAliasDecl(NamespaceAliasDecl *D);
  bool VisitLabelDecl(LabelDecl *D);
  bool VisitTypeDecl(TypeDecl *D);
  bool VisitTypedefNameDecl(TypedefNameDecl *D);
  // TypedefDecl empty
  // TypeAliasDecl empty
  bool VisitUnresolvedUsingTypenameDecl(UnresolvedUsingTypenameDecl *D);
  bool VisitTagDecl(TagDecl *D);
  bool VisitEnumDecl(EnumDecl *D);
  bool VisitRecordDecl(RecordDecl *D);
  bool VisitCXXRecordDecl(CXXRecordDecl *D);
  bool TraverseClassTemplateSpecializationDecl(ClassTemplateSpecializationDecl *D);
  bool VisitClassTemplateSpecializationDecl(ClassTemplateSpecializationDecl *D);
  bool VisitClassTemplatePartialSpecializationDecl(ClassTemplatePartialSpecializationDecl *D);
  bool VisitTemplateTypeParmDecl(TemplateTypeParmDecl *D);
  // ValueDecl empty
  bool VisitEnumConstantDecl(EnumConstantDecl *D);
  // UnresolvedUsingValueDecl empty
  bool TraverseIndirectFieldDecl(IndirectFieldDecl *D);
  // IndirectFieldDecl empty
  // DeclaratorDecl empty
  bool VisitFunctionDecl(FunctionDecl *D);
  bool VisitCXXMethodDecl(CXXMethodDecl *D);
  bool VisitCXXConstructorDecl(CXXConstructorDecl *D);
  bool VisitCXXDestructorDecl(CXXDestructorDecl *D);
  bool VisitCXXConversionDecl(CXXConversionDecl *D);
  bool VisitFieldDecl(FieldDecl *D);
  // TODO: ObjCIvarDecl
  // TODO: ObjCAtDefsFieldDecl
  bool VisitVarDecl(VarDecl *D);
  // ImplicitParamDecl empty
  // TODO: test ImplicitParamDecl (ObjC only?)
  bool VisitParmVarDecl(ParmVarDecl *D);
  bool VisitNonTypeTemplateParmDecl(NonTypeTemplateParmDecl *D);
  // TemplateDecl empty
  bool VisitRedeclarableTemplateDecl(RedeclarableTemplateDecl *D);
  // FunctionTemplateDecl empty
  // ClassTemplateDecl empty
  // TypeAliasTemplateDecl empty
  bool VisitTemplateTemplateParmDecl(TemplateTemplateParmDecl *D);
  bool VisitUsingDecl(UsingDecl *D);
  bool VisitUsingShadowDecl(UsingShadowDecl *D);
  // TODO: ObjCMethodDecl
  // TODO: ObjCContainerDecl
  // TODO: ObjCCategoryDecl
  // TODO: ObjCProtocolDecl
  // TODO: ObjCInterfaceDecl
  // TODO: ObjCImplDecl
  // TODO: ObjCCategoryImplDecl
  // TODO: ObjCImplementationDecl
  // TODO: ObjCPropertyDecl
  // TODO: ObjCCompatibleAliasDecl
  bool VisitLinkageSpecDecl(LinkageSpecDecl *D);
  // TODO: ObjCPropertyImplDecl
  // FileScopeAsmDecl empty
  bool VisitAccessSpecDecl(AccessSpecDecl *D);
  bool VisitFriendDecl(FriendDecl *D);
  // TODO: FriendTemplateDecl
  // TODO: StaticAssertDecl->isFailed()

  // Extensions
  // TODO: BlockDecl
  // TODO: ClassScopeFunctionSpecializationDecl
  // TODO: ImportDecl

  // Statements
  bool TraverseStmt(Stmt *S);
  bool VisitStmt(Stmt *S);
  bool VisitNullStmt(NullStmt *S);
  // CompoundStmt empty
  bool VisitLabelStmt(LabelStmt *S);
  bool VisitAttributedStmt(AttributedStmt *S);
  // IfStmt empty
  bool VisitSwitchStmt(SwitchStmt *S);
  // WhileStmt empty
  // DoStmt empty
  // ForStmt empty
  bool VisitGotoStmt(GotoStmt *S);
  // IndirectGotoStmt empty
  // ContinueStmt empty
  // BreakStmt empty
  bool VisitReturnStmt(ReturnStmt *S);
  // DeclStmt
  // SwitchCase empty
  // CaseStmt empty
  // DefaultStmt empty
  // AsmStmt empty
  bool VisitGCCAsmStmt(GCCAsmStmt *S);
  // TODO: MSAsmStmt

  // Obj-C statements
  // TODO: ObjCAtTryStmt
  // TODO: ObjCAtCatchStmt
  // TODO: ObjCAtFinallyStmt
  // TODO: ObjCAtThrowStmt
  // TODO: ObjCAtSynchronizedStmt
  // TODO: ObjCForCollectionStmt
  // TODO: ObjCAutoreleasePoolStmt

  // C++ statments
  // CXXCatchStmt empty
  // CXXTryStmt empty
  // CXXForRangeStmt empty

  // Expressions
  bool VisitExpr(Expr *E);
  bool VisitPredefinedExpr(PredefinedExpr *E);
  bool VisitDeclRefExpr(DeclRefExpr *E);
  bool VisitIntegerLiteral(IntegerLiteral *E);
  bool VisitFloatingLiteral(FloatingLiteral *E);
  // ImaginaryLiteral empty
  bool VisitStringLiteral(StringLiteral *E);
  bool VisitCharacterLiteral(CharacterLiteral *E);
  // ParenExpr empty
  bool VisitUnaryOperator(UnaryOperator *E);
  bool VisitOffsetOfExpr(OffsetOfExpr *E);
  bool VisitUnaryExprOrTypeTraitExpr(UnaryExprOrTypeTraitExpr *E);
  // ArraySubscriptExpr empty
  // CallExpr empty
  bool VisitMemberExpr(MemberExpr *E);
  bool VisitCastExpr(CastExpr *E);
  bool VisitBinaryOperator(BinaryOperator *E);
  bool VisitCompoundAssignOperator(CompoundAssignOperator *E);
  // AbstractConditionalOperator empty
  // ConditionalOperator empty
  // BinaryConditionalOperator empty
  // ImplicitCastExpr empty
  // ExplicitCastExpr empty
  // CStyleCastExpr empty
  bool TraverseCompoundLiteralExpr(CompoundLiteralExpr *E);
  bool VisitCompoundLiteralExpr(CompoundLiteralExpr *E);
  // TODO: ExtVectorElementExpr (attribute ext_vector_type)
  bool VisitInitListExpr(InitListExpr *E);
  bool VisitDesignatedInitExpr(DesignatedInitExpr *E);
  // TODO: ImplicitValueInitExpr
  // ParenListExpr empty
  // VAArgExpr empty
  // GenericSelectionExpr: TODO: isResultIndex()
  // TODO: PseudoObjectExpr

  // Atomic expressions
  bool VisitAtomicExpr(AtomicExpr *E);

  // GNU Extensions.
  bool VisitAddrLabelExpr(AddrLabelExpr *E);
  // StmtExpr empty
  // ChooseExpr empty
  // GNUNullExpr empty

  // C++ Expressions.
  // TODO: CXXOperatorCallExpr
  // TODO: CXXMemberCallExpr
  // CXXNamedCastExpr empty
  // CXXStaticCastExpr empty
  // CXXDynamicCastExpr empty
  // CXXReinterpretCastExpr empty
  // CXXConstCastExpr empty
  // CXXFunctionalCastExpr empty
  // TODO: CXXTypeidExpr
  // TODO: UserDefinedLiteral
  bool VisitCXXBoolLiteralExpr(CXXBoolLiteralExpr *E);
  // TODO: CXXNullPtrLiteralExpr
  // TODO: CXXThisExpr
  // TODO: CXXThrowExpr
  // TODO: CXXDefaultArgExpr
  // TODO: CXXScalarValueInitExpr
  // TODO: CXXNewExpr
  // TODO: CXXDeleteExpr
  // TODO: CXXPseudoDestructorExpr
  // TODO: TypeTraitExpr
  // TODO: UnaryTypeTraitExpr
  // TODO: BinaryTypeTraitExpr
  // TODO: ArrayTypeTraitExpr
  // TODO: ExpressionTraitExpr
  // TODO: DependentScopeDeclRefExpr
  // TODO: CXXConstructExpr
  // TODO: CXXBindTemporaryExpr
  // TODO: ExprWithCleanups
  // TODO: CXXTemporaryObjectExpr
  // TODO: CXXUnresolvedConstructExpr
  // TODO: CXXDependentScopeMemberExpr
  // TODO: OverloadExpr
  // TODO: UnresolvedLookupExpr
  // TODO: UnresolvedMemberExpr
  // TODO: CXXNoexceptExpr
  // TODO: PackExpansionExpr
  // TODO: SizeOfPackExpr
  // TODO: SubstNonTypeTemplateParmExpr
  // TODO: SubstNonTypeTemplateParmPackExpr
  // TODO: MaterializeTemporaryExpr
  // TODO: LambdaExpr

  // Obj-C Expressions.
  // TODO: ObjCStringLiteral
  // TODO: ObjCBoxedExpr
  // TODO: ObjCArrayLiteral
  // TODO: ObjCDictionaryLiteral
  // TODO: ObjCEncodeExpr
  // TODO: ObjCMessageExpr
  // TODO: ObjCSelectorExpr
  // TODO: ObjCProtocolExpr
  // TODO: ObjCIvarRefExpr
  // TODO: ObjCPropertyRefExpr
  // TODO: ObjCIsaExpr
  // TODO: ObjCIndirectCopyRestoreExpr
  // TODO: ObjCBoolLiteralExpr
  // TODO: ObjCSubscriptRefExpr

  // Obj-C ARC Expressions.
  // TODO: ObjCBridgedCastExpr

  // CUDA Expressions.
  // TODO: CUDAKernelCallExpr

  // Clang Extensions.
  // TODO: ShuffleVectorExpr
  // TODO: BlockExpr
  // OpaqueValueExpr empty

  // Microsoft Extensions.
  // TODO: CXXUuidofExpr
  // TODO: SEHTryStmt
  // TODO: SEHExceptStmt
  // TODO: SEHFinallyStmt
  // TODO: MSDependentExistsStmt

  // OpenCL Extensions.
  // TODO: AsTypeExpr

  bool TraverseType(QualType T);
  bool VisitType(Type *T);
  bool VisitBuiltinType(BuiltinType *T);
  bool VisitRecordType(RecordType *T);
  // TODO: Type

  bool TraverseTypeLoc(TypeLoc TL);
  bool VisitTypeLoc(TypeLoc TL);
  bool VisitQualifiedTypeLoc(QualifiedTypeLoc TL);
  bool TraverseSubstTemplateTypeParmTypeLoc(SubstTemplateTypeParmTypeLoc TL);
  // TODO: TypeLoc

  // TODO: Attr

  bool TraverseNestedNameSpecifier(NestedNameSpecifier *NNS);
  bool TraverseNestedNameSpecifierLoc(NestedNameSpecifierLoc NNS);
  bool TraverseDeclarationNameInfo(DeclarationNameInfo NameInfo);
  bool TraverseTemplateArgument(const TemplateArgument &Arg);
  bool TraverseTemplateArgumentLoc(const TemplateArgumentLoc &ArgLoc);
  bool TraverseConstructorInitializer(CXXCtorInitializer *Init);
*/

public:
	clang::ASTUnit& astUnit;
	clang::ASTContext& astContext;

	// Convenience methods to stringify some things.
	std::string declLocStr(const clang::Decl& decl);
	std::string typeStr(clang::QualType qualType);
};

} /* namespace astvisitors */
} /* namespace myclang */

#endif /* MYCLANG_ASTVISITORS_CLASSSOURCE_H_ */
