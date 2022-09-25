// © 2022 CronoGames


#include "ESAICharacter.h"
#include "CroActionComponent.h"
#include "ESAIController.h"
#include <BehaviorTree/BlackboardComponent.h>

bool AESAICharacter::AILineTrace(float TraceDistance, FHitResult& OutHit, ECollisionChannel TraceChannel /*= ECollisionChannel::ECC_Visibility*/, bool ShowDebug /*= false*/)
{
	AESAIController* MyController = Cast<AESAIController>(GetController());
	AActor* TargetActor = nullptr;
	if (MyController)
	{
		TargetActor = Cast<AActor>(MyController->GetBlackboardComponent()->GetValueAsObject(TargetActorKeyName));
	}


	FVector TraceStart = GetActorLocation();
	FVector TraceEnd;
	if (TargetActor)
	{
		FVector Direction = TargetActor->GetActorLocation() - GetActorLocation();
		TraceEnd = TraceStart + (Direction * TraceDistance);
	}
	else
	{
		TraceEnd = TraceStart + (GetMesh()->GetForwardVector() * TraceDistance);
	}

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult Hit;
	bool BlockingHit = GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannel, Params);
	//ShowDebug = true;
	if (ShowDebug)
	{
		FColor LineColor = BlockingHit ? FColor::Green : FColor::Red;
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, LineColor, false, 2.0f, 0, 2.0f);
	}
	OutHit = Hit;
	return BlockingHit;
}
