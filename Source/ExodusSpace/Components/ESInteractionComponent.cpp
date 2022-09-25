// © 2022 CronoGames


#include "ESInteractionComponent.h"
#include "../Character/Player/ESPlayerCharacter.h"
#include "../Interfaces/ESGamePlayInterface.h"
#include <Camera/CameraComponent.h>
#include "../UI/ESWorldUserWidget.h"

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

	APawn* MyPawn = Cast<APawn>(GetOwner());
	if (MyPawn && MyPawn->IsLocallyControlled())
	{
		FindInteractable();
	}
}

void UESInteractionComponent::FindInteractable()
{
	AActor* MyOwner = GetOwner();
	AESPlayerCharacter* PC = Cast<AESPlayerCharacter>(MyOwner);
	HitActor = nullptr;
	FHitResult Hit;
	bool BlockingHit = PC->CameraLineTrace(TraceDistance, Hit, CollisionChannel);
	if (BlockingHit)
	{
		HitActor = Hit.GetActor();
	}

	if (HitActor)
	{
		if (DefaultWidget == nullptr && ensure(DefaultWidgetClass))
		{
			DefaultWidget = CreateWidget<UESWorldUserWidget>(GetWorld(), DefaultWidgetClass);
		}
		if (DefaultWidget)
		{
			DefaultWidget->AttachedActor = HitActor;

			if (!DefaultWidget->IsInViewport())
			{
				DefaultWidget->AddToViewport();
			}
		}
		
	}
	else
	{
		if (DefaultWidget)
		{
			DefaultWidget->RemoveFromParent();
		}
	}
}

void UESInteractionComponent::Interact()
{
	ServerInteract(HitActor);
}

void UESInteractionComponent::ServerInteract_Implementation(AActor* InFocus)
{
	if (InFocus && InFocus->Implements<UESGamePlayInterface>())
	{
		APawn* Pawn = Cast<APawn>(GetOwner());
		IESGamePlayInterface::Execute_Interact(InFocus, Pawn);
	}
}
