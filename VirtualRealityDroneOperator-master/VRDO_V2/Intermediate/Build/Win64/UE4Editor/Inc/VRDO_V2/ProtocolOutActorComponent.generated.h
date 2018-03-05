// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FVector;
#ifdef VRDO_V2_ProtocolOutActorComponent_generated_h
#error "ProtocolOutActorComponent.generated.h already included, missing '#pragma once' in ProtocolOutActorComponent.h"
#endif
#define VRDO_V2_ProtocolOutActorComponent_generated_h

#define VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSendOutput) \
	{ \
		P_GET_STRUCT(FVector,Z_Param_fingerPosition); \
		P_GET_TARRAY(int32,Z_Param_droneIDs); \
		P_GET_PROPERTY(UStrProperty,Z_Param_actionType); \
		P_GET_TARRAY(FVector,Z_Param_dronePositions); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->SendOutput(Z_Param_fingerPosition,Z_Param_droneIDs,Z_Param_actionType,Z_Param_dronePositions); \
		P_NATIVE_END; \
	}


#define VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSendOutput) \
	{ \
		P_GET_STRUCT(FVector,Z_Param_fingerPosition); \
		P_GET_TARRAY(int32,Z_Param_droneIDs); \
		P_GET_PROPERTY(UStrProperty,Z_Param_actionType); \
		P_GET_TARRAY(FVector,Z_Param_dronePositions); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->SendOutput(Z_Param_fingerPosition,Z_Param_droneIDs,Z_Param_actionType,Z_Param_dronePositions); \
		P_NATIVE_END; \
	}


#define VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesUProtocolOutActorComponent(); \
	friend VRDO_V2_API class UClass* Z_Construct_UClass_UProtocolOutActorComponent(); \
	public: \
	DECLARE_CLASS(UProtocolOutActorComponent, UActorComponent, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/VRDO_V2"), NO_API) \
	DECLARE_SERIALIZER(UProtocolOutActorComponent) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_INCLASS \
	private: \
	static void StaticRegisterNativesUProtocolOutActorComponent(); \
	friend VRDO_V2_API class UClass* Z_Construct_UClass_UProtocolOutActorComponent(); \
	public: \
	DECLARE_CLASS(UProtocolOutActorComponent, UActorComponent, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/VRDO_V2"), NO_API) \
	DECLARE_SERIALIZER(UProtocolOutActorComponent) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UProtocolOutActorComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UProtocolOutActorComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UProtocolOutActorComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UProtocolOutActorComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UProtocolOutActorComponent(UProtocolOutActorComponent&&); \
	NO_API UProtocolOutActorComponent(const UProtocolOutActorComponent&); \
public:


#define VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UProtocolOutActorComponent(UProtocolOutActorComponent&&); \
	NO_API UProtocolOutActorComponent(const UProtocolOutActorComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UProtocolOutActorComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UProtocolOutActorComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UProtocolOutActorComponent)


#define VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_PRIVATE_PROPERTY_OFFSET
#define VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_15_PROLOG
#define VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_PRIVATE_PROPERTY_OFFSET \
	VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_RPC_WRAPPERS \
	VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_INCLASS \
	VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_PRIVATE_PROPERTY_OFFSET \
	VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_INCLASS_NO_PURE_DECLS \
	VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID VRDO_V2_Source_VRDO_V2_ProtocolOutActorComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
