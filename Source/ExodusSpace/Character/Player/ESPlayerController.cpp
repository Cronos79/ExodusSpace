// © 2022 CronoGames


#include "ESPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

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
	TArray<AActor*> ActorLoc;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), ActorLoc);
	Transform.SetLocation(ActorLoc[0]->GetActorLocation()); // #TODO: Get a real spawn location
	//Transform.SetRotation()
	Transform.SetScale3D(FVector3d(1.0f, 1.0f, 1.0f));

	return Transform;
}
