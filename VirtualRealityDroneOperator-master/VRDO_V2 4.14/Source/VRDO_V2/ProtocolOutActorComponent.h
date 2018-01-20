// Sends operator commands from the VR scene to the Master PC through the network

#pragma once

#include <string>
#include <iostream>
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

#include "Components/ActorComponent.h"
#include "ProtocolOutActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRDO_V2_API UProtocolOutActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProtocolOutActorComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintCallable, Category = "SendOutput")
	void SendOutput(FVector fingerPosition, TArray<int32> droneIDs, FString actionType, TArray<FVector> dronePositions);

	FSocket* SocketOut;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float posX;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float posY;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float posZ;
};
