// © 2022 CronoGames


#include "ESPlayerController.h"

void AESPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	OnPawnChanged.Broadcast(InPawn);
}
