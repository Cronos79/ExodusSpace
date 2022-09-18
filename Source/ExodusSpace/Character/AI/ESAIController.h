// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ESAIController.generated.h"

class UBehaviorTree;

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

protected:
	void BeginPlay() override;
	
};
