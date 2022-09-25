// © 2022 CronoGames


#include "ESBTTask_RangedAttack.h"
#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "ESAICharacter.h"

EBTNodeResult::Type UESBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = Cast<AAIController>(OwnerComp.GetAIOwner());
	if (ensure(MyController))
	{
		AESAICharacter* MyPawn = Cast<AESAICharacter>(MyController->GetPawn());
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		MyPawn->PrimaryAttack();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
