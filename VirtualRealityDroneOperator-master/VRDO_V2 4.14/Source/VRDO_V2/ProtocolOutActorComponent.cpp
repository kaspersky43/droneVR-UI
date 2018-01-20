// Sends operator commands from the VR scene to the Master PC through the network

#include "VRDO_V2.h"
#include "ProtocolOutActorComponent.h"
#include <string>
#include <iostream>
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include <math.h>

using namespace std;

string MASTER_IP = "169.254.26.174";
int32 MASTER_PORT = 63819;

// Sets default values for this component's properties
UProtocolOutActorComponent::UProtocolOutActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProtocolOutActorComponent::BeginPlay()
{
	Super::BeginPlay();

	SocketOut = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_DGram, TEXT("Description"), true);

	FString address = UTF8_TO_TCHAR(MASTER_IP.c_str());
	int32 port = MASTER_PORT;
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	bool connected = SocketOut->Connect(*addr);
	
	string output = connected ? "Output Connection Successful" : "Output Connection Failed";
	FString outputA(output.c_str());

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, outputA);
}

void UProtocolOutActorComponent::SendOutput(FVector fingerPosition, TArray<int32> droneIDs, FString actionType, TArray<FVector> dronePositions)
{
	FString spaces = " ";

	FString jsonBuilder = "{";
	// use dronePosition
	if (actionType == "TAKEOFF") {
		for (int i = 0; i < droneIDs.Num(); i++) {
			string id = to_string(droneIDs[i]);
			FString fid(id.c_str());
			jsonBuilder += "\"";
			jsonBuilder += fid;
			jsonBuilder += "\":{\"wp\":[[";

			float newX = (60.3 - (dronePositions[i][0] * -1)) / 200.0;
			float newY = (-69.389 + dronePositions[i][1]) / 200.0;
			float newZ = (dronePositions[i][2] - 10.0) / 200.0;

			jsonBuilder += FString::SanitizeFloat(newX);
			jsonBuilder += ",";
			jsonBuilder += FString::SanitizeFloat(newY);
			jsonBuilder += ",";
			jsonBuilder += "0.65";
			jsonBuilder += "]]},";
		}
		jsonBuilder = jsonBuilder.LeftChop(1);
		jsonBuilder += "}";
		UE_LOG(LogTemp, Error, TEXT("TAKEOFF: %s"), *jsonBuilder);

	} else if (actionType == "MOVE") {
		for (int i = 0; i < droneIDs.Num(); i++) {
			string id = to_string(droneIDs[i]);
			FString fid(id.c_str());
			jsonBuilder += "\"";
			jsonBuilder += fid;
			jsonBuilder += "\":{\"wp\":[[";

			float newX = (60.3 - (fingerPosition[0] * -1)) / 200.0;
			float newY = (-69.389 + fingerPosition[1]) / 200.0;
			float newZ = (fingerPosition[2] - 10.0) / 200.0;

			jsonBuilder += FString::SanitizeFloat(newX);
			jsonBuilder += ",";
			jsonBuilder += FString::SanitizeFloat(newY);
			jsonBuilder += ",";
			jsonBuilder += FString::SanitizeFloat(newZ);
			jsonBuilder += "]]},";
		}
		jsonBuilder = jsonBuilder.LeftChop(1);
		jsonBuilder += "}";
		UE_LOG(LogTemp, Error, TEXT("MOVE: %s"), *jsonBuilder);
	} else if (actionType == "LAND") {
		for (int i = 0; i < droneIDs.Num(); i++) {
			string id = to_string(droneIDs[i]);
			FString fid(id.c_str());
			jsonBuilder += "\"";
			jsonBuilder += fid;
			jsonBuilder += "\":{\"wp\":[[";

			float newX = (60.3 - (dronePositions[i][0] * -1)) / 200.0;
			float newY = (-69.389 + dronePositions[i][1]) / 200.0;
			float newZ = (dronePositions[i][2] - 10.0) / 200.0;

			jsonBuilder += FString::SanitizeFloat(newX);
			jsonBuilder += ",";
			jsonBuilder += FString::SanitizeFloat(newY);
			jsonBuilder += ",";
			jsonBuilder += "0.0";
			jsonBuilder += "]]},";
		}
		jsonBuilder = jsonBuilder.LeftChop(1);
		jsonBuilder += "}";
		UE_LOG(LogTemp, Error, TEXT("LAND: %s"), *jsonBuilder);
	} else if (actionType == "TRIANGLE") {
		for (int i = 0; i < droneIDs.Num(); i++) {
			string id = to_string(droneIDs[i]);
			FString fid(id.c_str());
			jsonBuilder += "\"";
			jsonBuilder += fid;
			jsonBuilder += "\":{\"wp\":[[";

			// lastX and lastY are current and ending positions, for triangle it is the smallest X and Y
			float lastX = (60.3 - (dronePositions[i][0] * -1)) / 200.0;
			float lastY = (-69.389 + dronePositions[i][1]) / 200.0;
			float newZ = (dronePositions[i][2] - 10.0) / 200.0;

			float firstX = lastX + 1.5; // .5;
			float firstY = lastY;

			float secondX = lastX + .75; // .25;
			float secondY = lastY + 1.299;

			jsonBuilder += FString::SanitizeFloat(firstX) + "," + FString::SanitizeFloat(firstY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(firstX) + "," + FString::SanitizeFloat(firstY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(firstX) + "," + FString::SanitizeFloat(firstY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(firstX) + "," + FString::SanitizeFloat(firstY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(firstX) + "," + FString::SanitizeFloat(firstY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(firstX) + "," + FString::SanitizeFloat(firstY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(firstX) + "," + FString::SanitizeFloat(firstY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(firstX) + "," + FString::SanitizeFloat(firstY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(firstX) + "," + FString::SanitizeFloat(firstY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(firstX) + "," + FString::SanitizeFloat(firstY) + "," + FString::SanitizeFloat(newZ) + "],[";

			jsonBuilder += FString::SanitizeFloat(secondX) + "," + FString::SanitizeFloat(secondY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(secondX) + "," + FString::SanitizeFloat(secondY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(secondX) + "," + FString::SanitizeFloat(secondY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(secondX) + "," + FString::SanitizeFloat(secondY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(secondX) + "," + FString::SanitizeFloat(secondY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(secondX) + "," + FString::SanitizeFloat(secondY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(secondX) + "," + FString::SanitizeFloat(secondY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(secondX) + "," + FString::SanitizeFloat(secondY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(secondX) + "," + FString::SanitizeFloat(secondY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(secondX) + "," + FString::SanitizeFloat(secondY) + "," + FString::SanitizeFloat(newZ) + "],[";

			jsonBuilder += FString::SanitizeFloat(lastX) + "," + FString::SanitizeFloat(lastY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(lastX) + "," + FString::SanitizeFloat(lastY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(lastX) + "," + FString::SanitizeFloat(lastY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(lastX) + "," + FString::SanitizeFloat(lastY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(lastX) + "," + FString::SanitizeFloat(lastY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(lastX) + "," + FString::SanitizeFloat(lastY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(lastX) + "," + FString::SanitizeFloat(lastY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(lastX) + "," + FString::SanitizeFloat(lastY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(lastX) + "," + FString::SanitizeFloat(lastY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(lastX) + "," + FString::SanitizeFloat(lastY) + "," + FString::SanitizeFloat(newZ) + "]";
			jsonBuilder += "]},";
		}
		jsonBuilder = jsonBuilder.LeftChop(1);
		jsonBuilder += "}";
		UE_LOG(LogTemp, Error, TEXT("TRIANGLE: %s"), *jsonBuilder);
	} else if (actionType == "CIRCLE") {
		for (int i = 0; i < droneIDs.Num(); i++) {
			string id = to_string(droneIDs[i]);
			FString fid(id.c_str());
			jsonBuilder += "\"";
			jsonBuilder += fid;
			jsonBuilder += "\":{\"wp\":[[";

			// (x-centerX)^2 + (y-centerY)^2 = .25
			// current X and Y are the center
			float centerX = (60.3 - (dronePositions[i][0] * -1)) / 200.0;
			float centerY = (-69.389 + dronePositions[i][1]) / 200.0;
			float newZ = (dronePositions[i][2] - 10.0) / 200.0;

			float theta = .5 / 3;

			float firstX = centerX;
			float firstY = sqrt(.25 - pow(firstX - centerX, 2.0)) + centerY;

			float secondX = firstX + theta;
			float secondY = sqrt(.25 - pow(secondX - centerX, 2.0)) + centerY;

			float thirdX = secondX + theta;
			float thirdY = sqrt(.25 - pow(thirdX - centerX, 2.0)) + centerY;

			float fourthX = thirdX + theta;
			float fourthY = sqrt(.25 - pow(fourthX - centerX, 2.0)) + centerY;

			float fifthX = thirdX;
			float fifthY = -1 * sqrt(.25 - pow(fifthX - centerX, 2.0)) + centerY;

			float sixthX = secondX;
			float sixthY = -1 * sqrt(.25 - pow(sixthX - centerX, 2.0)) + centerY;

			float seventhX = firstX;
			float seventhY = -1 * sqrt(.25 - pow(seventhX - centerX, 2.0)) + centerY;

			float eighthX = firstX - theta;
			float eighthY = sixthY;

			float ninthX = eighthX - theta;
			float ninthY = fifthY;

			float tenthX = ninthX - theta;
			float tenthY = fourthY;

			float eleventhX = tenthX + theta;
			float eleventhY = thirdY;

			float twelthX = eleventhX + theta;
			float twelthY = secondY;

			jsonBuilder += FString::SanitizeFloat(firstX) + "," + FString::SanitizeFloat(firstY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(secondX) + "," + FString::SanitizeFloat(secondY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(thirdX) + "," + FString::SanitizeFloat(thirdY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(fourthX) + "," + FString::SanitizeFloat(fourthY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(fifthX) + "," + FString::SanitizeFloat(fifthY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(sixthX) + "," + FString::SanitizeFloat(sixthY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(seventhX) + "," + FString::SanitizeFloat(seventhY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(eighthX) + "," + FString::SanitizeFloat(eighthY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(ninthX) + "," + FString::SanitizeFloat(ninthY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(tenthX) + "," + FString::SanitizeFloat(tenthY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(eleventhX) + "," + FString::SanitizeFloat(eleventhY) + "," + FString::SanitizeFloat(newZ) + "],[";
			jsonBuilder += FString::SanitizeFloat(twelthX) + "," + FString::SanitizeFloat(twelthY) + "," + FString::SanitizeFloat(newZ) + "]";
			jsonBuilder += "]},";
		}
		jsonBuilder = jsonBuilder.LeftChop(1);
		jsonBuilder += "}";
		UE_LOG(LogTemp, Error, TEXT("CIRCLE: %s"), *jsonBuilder);
	}

	TCHAR *serializedOut = jsonBuilder.GetCharArray().GetData();
	int32 sizeOut = FCString::Strlen(serializedOut);
	int32 sent = 0;
	bool successfulOut = SocketOut->Send((uint8*)TCHAR_TO_UTF8(serializedOut), sizeOut, sent);
}

// Called every frame
void UProtocolOutActorComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

