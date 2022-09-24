// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CroActionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCroActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CROACTION_API ICroActionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	float GetCurrentMana();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	bool UseMana(float Amount);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	bool HasEnoughMana(float Value);
};
