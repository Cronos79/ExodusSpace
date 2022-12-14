// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ESBTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class EXODUSSPACE_API UESBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector IsInRangeKey;
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetActorKey;
	UPROPERTY(EditAnywhere, Category = "AI")
	float MaxRange{2000.0f};

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
