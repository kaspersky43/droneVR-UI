// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include <iostream>
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

#include "Components/ActorComponent.h"
#include "ProtocolInActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRDO_V2_API UProtocolInActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProtocolInActorComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	FSocket* SocketIn;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		int droneID;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float posX;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float posY;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float posZ;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float angX;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float angY;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float angZ;
};
