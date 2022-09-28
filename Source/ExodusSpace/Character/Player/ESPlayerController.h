// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <Delegates/DelegateCombinations.h>
#include "ESPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnChanged, APawn*, NewPawn);

/**
 * 
 */
UCLASS()
class EXODUSSPACE_API AESPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	FOnPawnChanged OnPawnChanged;
	void SetPawn(APawn* InPawn) override;
};
