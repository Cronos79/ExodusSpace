// © 2022 CronoGames


#include "ESBTService_CheckAttackRange.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <AIController.h>

void UESBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Check distance between ai pawn and the target
	UBlackboardComponent* BBC = OwnerComp.GetBlackboardComponent();
	if (ensure(BBC))
	{
		AActor* TargetActor = Cast<AActor>(BBC->GetValueAsObject(TargetActorKey.SelectedKeyName));
		if (TargetActor)
		{
			AAIController* AIC = OwnerComp.GetAIOwner();
			if (ensure(AIC))
			{
				APawn* AIPawn = AIC->GetPawn();
				if (ensure(AIPawn))
				{
					float Distance = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					bool bWithInRange = Distance < MaxRange;
					bool bHasLOS = false;
					if (bWithInRange)
					{
						bHasLOS = AIC->LineOfSightTo(TargetActor);
					}					

					BBC->SetValueAsBool(IsInRangeKey.SelectedKeyName, (bHasLOS && bWithInRange));
				}
			}
		}
	}
}
