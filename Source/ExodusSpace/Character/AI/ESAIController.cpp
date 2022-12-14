// © 2022 CronoGames


#include "ESAIController.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackboardComponent.h"

void AESAIController::BeginPlay()
{
	Super::BeginPlay();
	if (ensure(BehaviorTree))
	{
		RunBehaviorTree(BehaviorTree);
	}

	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (MyPawn)
	{
		GetBlackboardComponent()->SetValueAsVector("TargetLocation", MyPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	}
}