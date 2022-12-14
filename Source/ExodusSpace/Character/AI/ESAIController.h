// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ESAIController.generated.h"

class UBehaviorTree;
class UAISenseConfig_Sight;

/**
 * 
 */
UCLASS()
class EXODUSSPACE_API AESAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;
	UPROPERTY()
	UAISenseConfig_Sight* SightSense;

protected:
	void BeginPlay() override;
	
};
