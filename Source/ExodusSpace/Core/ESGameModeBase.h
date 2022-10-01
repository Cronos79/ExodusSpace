// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ESGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class EXODUSSPACE_API AESGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void SaveGame();
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void LoadGame();
	
};
