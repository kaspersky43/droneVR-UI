// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Boilerplate C++ definitions for a single module.
	This is automatically generated by UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "VRDO_V2.h"
#include "GeneratedCppIncludes.h"
#include "VRDO_V2.generated.dep.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCode1VRDO_V2() {}
	void UProtocolInActorComponent::StaticRegisterNativesUProtocolInActorComponent()
	{
	}
	IMPLEMENT_CLASS(UProtocolInActorComponent, 1531353190);
	void UProtocolOutActorComponent::StaticRegisterNativesUProtocolOutActorComponent()
	{
		FNativeFunctionRegistrar::RegisterFunction(UProtocolOutActorComponent::StaticClass(), "SendOutput",(Native)&UProtocolOutActorComponent::execSendOutput);
	}
	IMPLEMENT_CLASS(UProtocolOutActorComponent, 3357225224);
#if USE_COMPILED_IN_NATIVES
// Cross Module References
	ENGINE_API class UClass* Z_Construct_UClass_UActorComponent();
	COREUOBJECT_API class UScriptStruct* Z_Construct_UScriptStruct_FVector();

	VRDO_V2_API class UClass* Z_Construct_UClass_UProtocolInActorComponent_NoRegister();
	VRDO_V2_API class UClass* Z_Construct_UClass_UProtocolInActorComponent();
	VRDO_V2_API class UFunction* Z_Construct_UFunction_UProtocolOutActorComponent_SendOutput();
	VRDO_V2_API class UClass* Z_Construct_UClass_UProtocolOutActorComponent_NoRegister();
	VRDO_V2_API class UClass* Z_Construct_UClass_UProtocolOutActorComponent();
	VRDO_V2_API class UPackage* Z_Construct_UPackage__Script_VRDO_V2();
	UClass* Z_Construct_UClass_UProtocolInActorComponent_NoRegister()
	{
		return UProtocolInActorComponent::StaticClass();
	}
	UClass* Z_Construct_UClass_UProtocolInActorComponent()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UActorComponent();
			Z_Construct_UPackage__Script_VRDO_V2();
			OuterClass = UProtocolInActorComponent::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20B00080;


PRAGMA_DISABLE_DEPRECATION_WARNINGS
				UProperty* NewProp_angZ = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("angZ"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(angZ, UProtocolInActorComponent), 0x0010000000020005);
				UProperty* NewProp_angY = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("angY"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(angY, UProtocolInActorComponent), 0x0010000000020005);
				UProperty* NewProp_angX = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("angX"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(angX, UProtocolInActorComponent), 0x0010000000020005);
				UProperty* NewProp_posZ = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("posZ"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(posZ, UProtocolInActorComponent), 0x0010000000020005);
				UProperty* NewProp_posY = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("posY"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(posY, UProtocolInActorComponent), 0x0010000000020005);
				UProperty* NewProp_posX = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("posX"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(posX, UProtocolInActorComponent), 0x0010000000020005);
				UProperty* NewProp_droneID = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("droneID"), RF_Public|RF_Transient|RF_MarkAsNative) UUnsizedIntProperty(CPP_PROPERTY_BASE(droneID, UProtocolInActorComponent), 0x0010000000020005);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("BlueprintSpawnableComponent"), TEXT(""));
				MetaData->SetValue(OuterClass, TEXT("ClassGroupNames"), TEXT("Custom"));
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("ProtocolInActorComponent.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("ProtocolInActorComponent.h"));
				MetaData->SetValue(NewProp_angZ, TEXT("Category"), TEXT("ProtocolInActorComponent"));
				MetaData->SetValue(NewProp_angZ, TEXT("ModuleRelativePath"), TEXT("ProtocolInActorComponent.h"));
				MetaData->SetValue(NewProp_angY, TEXT("Category"), TEXT("ProtocolInActorComponent"));
				MetaData->SetValue(NewProp_angY, TEXT("ModuleRelativePath"), TEXT("ProtocolInActorComponent.h"));
				MetaData->SetValue(NewProp_angX, TEXT("Category"), TEXT("ProtocolInActorComponent"));
				MetaData->SetValue(NewProp_angX, TEXT("ModuleRelativePath"), TEXT("ProtocolInActorComponent.h"));
				MetaData->SetValue(NewProp_posZ, TEXT("Category"), TEXT("ProtocolInActorComponent"));
				MetaData->SetValue(NewProp_posZ, TEXT("ModuleRelativePath"), TEXT("ProtocolInActorComponent.h"));
				MetaData->SetValue(NewProp_posY, TEXT("Category"), TEXT("ProtocolInActorComponent"));
				MetaData->SetValue(NewProp_posY, TEXT("ModuleRelativePath"), TEXT("ProtocolInActorComponent.h"));
				MetaData->SetValue(NewProp_posX, TEXT("Category"), TEXT("ProtocolInActorComponent"));
				MetaData->SetValue(NewProp_posX, TEXT("ModuleRelativePath"), TEXT("ProtocolInActorComponent.h"));
				MetaData->SetValue(NewProp_droneID, TEXT("Category"), TEXT("ProtocolInActorComponent"));
				MetaData->SetValue(NewProp_droneID, TEXT("ModuleRelativePath"), TEXT("ProtocolInActorComponent.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UProtocolInActorComponent(Z_Construct_UClass_UProtocolInActorComponent, &UProtocolInActorComponent::StaticClass, TEXT("UProtocolInActorComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UProtocolInActorComponent);
	UFunction* Z_Construct_UFunction_UProtocolOutActorComponent_SendOutput()
	{
		struct ProtocolOutActorComponent_eventSendOutput_Parms
		{
			FVector fingerPosition;
			TArray<int32> droneIDs;
			FString actionType;
			TArray<FVector> dronePositions;
		};
		UObject* Outer=Z_Construct_UClass_UProtocolOutActorComponent();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("SendOutput"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04820401, 65535, sizeof(ProtocolOutActorComponent_eventSendOutput_Parms));
			UProperty* NewProp_dronePositions = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("dronePositions"), RF_Public|RF_Transient|RF_MarkAsNative) UArrayProperty(CPP_PROPERTY_BASE(dronePositions, ProtocolOutActorComponent_eventSendOutput_Parms), 0x0010000000000080);
			UProperty* NewProp_dronePositions_Inner = new(EC_InternalUseOnlyConstructor, NewProp_dronePositions, TEXT("dronePositions"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000, Z_Construct_UScriptStruct_FVector());
			UProperty* NewProp_actionType = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("actionType"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(actionType, ProtocolOutActorComponent_eventSendOutput_Parms), 0x0010000000000080);
			UProperty* NewProp_droneIDs = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("droneIDs"), RF_Public|RF_Transient|RF_MarkAsNative) UArrayProperty(CPP_PROPERTY_BASE(droneIDs, ProtocolOutActorComponent_eventSendOutput_Parms), 0x0010000000000080);
			UProperty* NewProp_droneIDs_Inner = new(EC_InternalUseOnlyConstructor, NewProp_droneIDs, TEXT("droneIDs"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000);
			UProperty* NewProp_fingerPosition = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("fingerPosition"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(fingerPosition, ProtocolOutActorComponent_eventSendOutput_Parms), 0x0010000000000080, Z_Construct_UScriptStruct_FVector());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("SendOutput"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("ProtocolOutActorComponent.h"));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UProtocolOutActorComponent_NoRegister()
	{
		return UProtocolOutActorComponent::StaticClass();
	}
	UClass* Z_Construct_UClass_UProtocolOutActorComponent()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UActorComponent();
			Z_Construct_UPackage__Script_VRDO_V2();
			OuterClass = UProtocolOutActorComponent::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20B00080;

				OuterClass->LinkChild(Z_Construct_UFunction_UProtocolOutActorComponent_SendOutput());

PRAGMA_DISABLE_DEPRECATION_WARNINGS
				UProperty* NewProp_posZ = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("posZ"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(posZ, UProtocolOutActorComponent), 0x0010000000020005);
				UProperty* NewProp_posY = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("posY"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(posY, UProtocolOutActorComponent), 0x0010000000020005);
				UProperty* NewProp_posX = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("posX"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(posX, UProtocolOutActorComponent), 0x0010000000020005);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UProtocolOutActorComponent_SendOutput(), "SendOutput"); // 464192821
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("BlueprintSpawnableComponent"), TEXT(""));
				MetaData->SetValue(OuterClass, TEXT("ClassGroupNames"), TEXT("Custom"));
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("ProtocolOutActorComponent.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("ProtocolOutActorComponent.h"));
				MetaData->SetValue(NewProp_posZ, TEXT("Category"), TEXT("ProtocolOutActorComponent"));
				MetaData->SetValue(NewProp_posZ, TEXT("ModuleRelativePath"), TEXT("ProtocolOutActorComponent.h"));
				MetaData->SetValue(NewProp_posY, TEXT("Category"), TEXT("ProtocolOutActorComponent"));
				MetaData->SetValue(NewProp_posY, TEXT("ModuleRelativePath"), TEXT("ProtocolOutActorComponent.h"));
				MetaData->SetValue(NewProp_posX, TEXT("Category"), TEXT("ProtocolOutActorComponent"));
				MetaData->SetValue(NewProp_posX, TEXT("ModuleRelativePath"), TEXT("ProtocolOutActorComponent.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UProtocolOutActorComponent(Z_Construct_UClass_UProtocolOutActorComponent, &UProtocolOutActorComponent::StaticClass, TEXT("UProtocolOutActorComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UProtocolOutActorComponent);
	UPackage* Z_Construct_UPackage__Script_VRDO_V2()
	{
		static UPackage* ReturnPackage = NULL;
		if (!ReturnPackage)
		{
			ReturnPackage = CastChecked<UPackage>(StaticFindObjectFast(UPackage::StaticClass(), NULL, FName(TEXT("/Script/VRDO_V2")), false, false));
			ReturnPackage->SetPackageFlags(PKG_CompiledIn | 0x00000000);
			FGuid Guid;
			Guid.A = 0x53C7B216;
			Guid.B = 0x4A15AA63;
			Guid.C = 0x00000000;
			Guid.D = 0x00000000;
			ReturnPackage->SetGuid(Guid);

		}
		return ReturnPackage;
	}
#endif

PRAGMA_ENABLE_DEPRECATION_WARNINGS
