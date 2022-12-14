// © 2022 CronoGames


#include "ESBTTask_RangedAttack.h"
#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "ESAICharacter.h"

EBTNodeResult::Type UESBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = Cast<AAIController>(OwnerComp.GetAIOwner());
	AActor* NewProj = nullptr;
	if (ensure(MyController))
	{
		AESAICharacter* MyPawn = Cast<AESAICharacter>(MyController->GetPawn());
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName));
		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		// #TODO: Get a socket for the gun/hand
		FVector Direction = TargetActor->GetActorLocation() - MyPawn->GetActorLocation();
		FRotator MyRotation = Direction.Rotation();

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Params.Instigator = MyPawn;

		NewProj = GetWorld()->SpawnActor<AActor>(ProjectileClass, MyPawn->GetActorLocation(), MyRotation, Params);

		//MyPawn->PrimaryAttack();
	}

	return NewProj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
