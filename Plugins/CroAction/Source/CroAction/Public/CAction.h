// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CROACTION_API UCAction : public UObject
{
	GENERATED_BODY()
	
public:
	/* Action name to start and stop actions */
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

public:
	UWorld* GetWorld() const override;

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* Instigator);
};
