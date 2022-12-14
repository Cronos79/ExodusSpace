// © 2022 CronoGames


#include "ESInteractionComponent.h"
#include "../Character/Player/ESPlayerCharacter.h"
#include "../Interfaces/ESGamePlayInterface.h"
#include <Camera/CameraComponent.h>

// Sets default values for this component's properties
UESInteractionComponent::UESInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UESInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UESInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UESInteractionComponent::Interact()
{
	AActor* MyOwner = GetOwner();
	AESPlayerCharacter* PC = Cast<AESPlayerCharacter>(MyOwner);
	FHitResult Hit;
	bool BlockingHit = PC->CameraLineTrace(5000, Hit);
	if (BlockingHit)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			UE_LOG(LogTemp, Log, TEXT("Hit actor %s"), *HitActor->GetName());
			if (HitActor->Implements<UESGamePlayInterface>())
			{
				APawn* Pawn = Cast<APawn>(MyOwner);
				IESGamePlayInterface::Execute_Interact(HitActor, Pawn);
			}
		}
	}
}

