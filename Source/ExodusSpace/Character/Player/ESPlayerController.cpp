// © 2022 CronoGames


#include "ESPlayerController.h"

void AESPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	OnPawnChanged.Broadcast(InPawn);
}

TArray<FPlayerClasses> AESPlayerController::GetPlayerClasses()
{
	return PlayerClassOptions;
}

FTransform AESPlayerController::GetSpawnTransform()
{
	FTransform Transform;

	Transform.SetLocation(FVector(300.0f, 300.0f, 300.0f)); // #TODO: Get a real spawn location
	//Transform.SetRotation()
	Transform.SetScale3D(FVector3d(1.0f, 1.0f, 1.0f));

	return Transform;
}
