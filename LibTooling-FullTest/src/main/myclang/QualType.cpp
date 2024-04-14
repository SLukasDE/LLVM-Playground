#include "myclang/QualType.h"

#include "clang/AST/DeclTemplate.h"
#include "clang/AST/TemplateBase.h"
#include "clang/AST/TemplateName.h"

#include "llvm/Support/Casting.h"
#include "llvm/Support/raw_ostream.h"                      // llvm::raw_ostream

namespace myclang {

void QualType::dump(const clang::QualType& qualType, std::size_t d, clang::SourceManager& sourceManager, const clang::LangOptions& langOptions) {
	llvm::outs() << std::string(2*d, ' ') << "\n";
	llvm::outs() << std::string(2*d, ' ') << "DUMP-TYPE\n";
	llvm::outs() << std::string(2*d, ' ') << "---------\n";
	const clang::Type& type = *qualType;

	llvm::outs() << std::string(2*d, ' ') << "Type:      '" << qualType.getAsString() << "'\n";
	llvm::outs() << std::string(2*d, ' ') << "TypeClass: '" << type.getTypeClassName() << "'\n";

	//clang::Type::TypeClass classType = type.getTypeClass();
	clang::Type::TypeClass classType = qualType->getTypeClass();
	switch (classType) {

	// Pointer types.
	case clang::Type::Pointer:
		break;
	case clang::Type::BlockPointer:
		break;
	case clang::Type::MemberPointer:
		break;
	case clang::Type::ObjCObjectPointer:
		break;

	// Dependent types that could instantiate to pointer types.
	case clang::Type::UnresolvedUsing:
		break;
	case clang::Type::TypeOfExpr:
		break;
	case clang::Type::TypeOf:
		break;
	case clang::Type::Decltype:
		break;
	case clang::Type::UnaryTransform:
		break;
	case clang::Type::TemplateTypeParm:
		break;
	case clang::Type::SubstTemplateTypeParmPack:
		break;
	case clang::Type::DependentName:
		break;
	case clang::Type::DependentTemplateSpecialization:
		break;
	case clang::Type::Auto:
		break;

	// Dependent template specializations can instantiate to pointer
	// types unless they're known to be specializations of a class
	// template.
	case clang::Type::TemplateSpecialization: {
		auto templateSpecialization = qualType->getAs<clang::TemplateSpecializationType>();
		if (templateSpecialization->isTypeAlias()) {
			dump(templateSpecialization->getAliasedType(), d+1, sourceManager, langOptions);
			break;
		}

		std::string templateType = templateSpecialization->getTemplateName().getAsTemplateDecl()->getQualifiedNameAsString();
		llvm::outs() << std::string(2*d, ' ') << templateType << "<";

		auto numArgs = templateSpecialization->getNumArgs();
		for (unsigned int i = 0; i < numArgs; ++i) {
			if (i > 0) {
				llvm::outs() << ", ";
			}

			const clang::TemplateArgument& templateArg = templateSpecialization->getArg(i);
			if (templateArg.getKind() == clang::TemplateArgument::ArgKind::Type) {
				dump(templateArg.getAsType(), d+1, sourceManager, langOptions);
			}
		}

		llvm::outs() << ">\n";
		break;
	}


	case clang::Type::Builtin: {
		const clang::BuiltinType* builtinType = llvm::cast<clang::BuiltinType>(qualType.getTypePtr());

		if(!builtinType) {
			break;
		}

#if 0
		// MORE THAN 100 ENUMERATION VALUES !!!

		switch (builtinType->getKind()) {
		// Dependent types that could instantiate to a pointer type.
		case clang::BuiltinType::Dependent:
		case clang::BuiltinType::Overload:
		case clang::BuiltinType::BoundMember:
		case clang::BuiltinType::PseudoObject:
		case clang::BuiltinType::UnknownAny:
		case clang::BuiltinType::ARCUnbridgedCast:

		// Others
		case clang::BuiltinType::Void:
		case clang::BuiltinType::BuiltinFn:
		case clang::BuiltinType::NullPtr:
		// ...

		// OpenCL types
		case clang::BuiltinType::OCLSampler:
		case clang::BuiltinType::OCLEvent:
		case clang::BuiltinType::OCLClkEvent:
		case clang::BuiltinType::OCLQueue:
		case clang::BuiltinType::OCLReserveID:
		// ...

		// OpenMP types
		case clang::BuiltinType::OMPArraySection:
		// ...

		case clang::BuiltinType::ObjCId:
		case clang::BuiltinType::ObjCClass:
		case clang::BuiltinType::ObjCSel:
		}
#endif
	    break;
	}


	// Non-pointer types.
	case clang::Type::Complex:
		break;
	case clang::Type::LValueReference:
		break;
	case clang::Type::RValueReference:
		break;
	case clang::Type::ConstantArray:
		break;
	case clang::Type::IncompleteArray:
		break;
	case clang::Type::VariableArray:
		break;
	case clang::Type::DependentSizedArray:
		break;
	case clang::Type::DependentVector:
		break;
	case clang::Type::DependentSizedExtVector:
		break;
	case clang::Type::Vector:
		break;
	case clang::Type::ExtVector:
		break;
	case clang::Type::DependentAddressSpace:
		break;
	case clang::Type::FunctionProto:
		break;
	case clang::Type::FunctionNoProto:
		break;
	case clang::Type::Record: {
		const auto record = qualType->getAs<clang::RecordType>();
		std::string recordQualifiedName = record->getAsRecordDecl()->getQualifiedNameAsString();
		llvm::outs() << std::string(2*d, ' ') << recordQualifiedName << "\n";
		break;
	}
	case clang::Type::DeducedTemplateSpecialization:
		break;
	case clang::Type::Enum:
		break;
	case clang::Type::InjectedClassName:
		break;
	case clang::Type::PackExpansion:
		break;
	case clang::Type::ObjCObject:
		break;
	case clang::Type::ObjCInterface:
		break;
	case clang::Type::Atomic:
		break;
	case clang::Type::Pipe:
		break;

	case clang::Type::Typedef: {
		auto typedefType = qualType->getAs<clang::TypedefType>();
		dump(typedefType->desugar(), d+1, sourceManager, langOptions);
		break;
	}
	case clang::Type::Elaborated: {
		auto elaboratedType = qualType->getAs<clang::ElaboratedType>();
		dump(elaboratedType->desugar(), d+1, sourceManager, langOptions);
		break;
	}
	case clang::Type::SubstTemplateTypeParm: {
		auto substTemplateType = qualType->getAs<clang::SubstTemplateTypeParmType>();
		dump(substTemplateType->desugar(), d+1, sourceManager, langOptions);
		//Also tried getReplacementType.
		//walkType(substTemplateType->getReplacementType());
		break;
	}
	case clang::Type::Adjusted:
		break;
	case clang::Type::Decayed:
		break;
	case clang::Type::Attributed:
		break;
	case clang::Type::MacroQualified:
		break;
	case clang::Type::ObjCTypeParam:
		break;
	case clang::Type::Paren:
		break;
	}
}

} /* namespace myclang */
