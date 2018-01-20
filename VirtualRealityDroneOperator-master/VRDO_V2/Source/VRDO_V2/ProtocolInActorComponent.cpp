// This class reads drone positional and rotational data passed from the Streaming PC over the network
// It is deprecated, as the Motive Plugin in Unreal Engine is much smoother 

#include "VRDO_V2.h"
#include "ProtocolInActorComponent.h"
#include <string>
#include <iostream>
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

using namespace std;

// Sets default values for this component's properties
UProtocolInActorComponent::UProtocolInActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProtocolInActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// When the scene starts, create the socket to read from
	SocketIn = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_DGram, TEXT("Description"), true);

	FString address = TEXT("169.254.130.255");
	int32 port = 63921;
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);


	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	bool connected = SocketIn->Bind(*addr);

	// Prints whether or not the connection has been successfully made
	string outputC = connected ? "Input Connection Successful" : "Input Connection Failed";
	FString outputConnected(outputC.c_str());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, outputConnected);
}


// Called every frame
void UProtocolInActorComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	uint32 PendingData;

	bool x = SocketIn->HasPendingData(PendingData);

	if (PendingData > 0)
	{
		uint8 *Recv = new uint8[PendingData];
		int32 BytesRead;

		SocketIn->Recv(Recv, PendingData, BytesRead);

		std::string s(Recv, Recv + PendingData);

		sscanf_s((char*)Recv, "%d %f %f %f %f %f %f", &droneID, &posX, &posY, &posZ, &angX, &angY, &angZ);

		UE_LOG(LogTemp, Error, TEXT("%d %f %f %f %f %f %f"), &droneID, posX, posY, posZ, angX, angY, angZ);
	}
}

void UProtocolInActorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	UE_LOG(LogTemp, Error, TEXT("ENDED"));
	SocketIn->Close();
}
