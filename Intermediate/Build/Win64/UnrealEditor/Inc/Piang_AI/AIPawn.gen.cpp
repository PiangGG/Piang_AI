// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Piang_AI/Public/AIPawn.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAIPawn() {}
// Cross Module References
	PIANG_AI_API UClass* Z_Construct_UClass_AAIPawn_NoRegister();
	PIANG_AI_API UClass* Z_Construct_UClass_AAIPawn();
	ENGINE_API UClass* Z_Construct_UClass_APawn();
	UPackage* Z_Construct_UPackage__Script_Piang_AI();
// End Cross Module References
	void AAIPawn::StaticRegisterNativesAAIPawn()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AAIPawn);
	UClass* Z_Construct_UClass_AAIPawn_NoRegister()
	{
		return AAIPawn::StaticClass();
	}
	struct Z_Construct_UClass_AAIPawn_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AAIPawn_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APawn,
		(UObject* (*)())Z_Construct_UPackage__Script_Piang_AI,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAIPawn_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "AIPawn.h" },
		{ "ModuleRelativePath", "Public/AIPawn.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AAIPawn_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAIPawn>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AAIPawn_Statics::ClassParams = {
		&AAIPawn::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AAIPawn_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AAIPawn_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AAIPawn()
	{
		if (!Z_Registration_Info_UClass_AAIPawn.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AAIPawn.OuterSingleton, Z_Construct_UClass_AAIPawn_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AAIPawn.OuterSingleton;
	}
	template<> PIANG_AI_API UClass* StaticClass<AAIPawn>()
	{
		return AAIPawn::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AAIPawn);
	struct Z_CompiledInDeferFile_FID_ColorCube_Plugins_Piang_AI_Source_Piang_AI_Public_AIPawn_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ColorCube_Plugins_Piang_AI_Source_Piang_AI_Public_AIPawn_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AAIPawn, AAIPawn::StaticClass, TEXT("AAIPawn"), &Z_Registration_Info_UClass_AAIPawn, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AAIPawn), 4119572314U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ColorCube_Plugins_Piang_AI_Source_Piang_AI_Public_AIPawn_h_3919780814(TEXT("/Script/Piang_AI"),
		Z_CompiledInDeferFile_FID_ColorCube_Plugins_Piang_AI_Source_Piang_AI_Public_AIPawn_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ColorCube_Plugins_Piang_AI_Source_Piang_AI_Public_AIPawn_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
