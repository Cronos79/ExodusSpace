// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "../ESCharacter.h"
#include <BehaviorTree/BehaviorTreeTypes.h>
#include "ESAICharacter.generated.h"



/**
 * 
 */
UCLASS()
class EXODUSSPACE_API AESAICharacter : public AESCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "AI")
	FName TargetActorKeyName;
	
public:
	UFUNCTION()
	bool AILineTrace(float TraceDistance, FHitResult& Hit, ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility, bool ShowDebug = false);
};
