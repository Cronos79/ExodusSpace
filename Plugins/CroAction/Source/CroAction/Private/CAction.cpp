// © 2022 CronoGames


#include "CAction.h"
#include <CroActionComponent.h>
#include <CroActionInterface.h>

bool UCAction::IsRunning() const
{
	return bIsRunning;
}

UWorld* UCAction::GetWorld() const
{
	UActorComponent* ActorComp = Cast<UActorComponent>(GetOuter());
	if (ActorComp)
	{
		return ActorComp->GetWorld();
	}
	return nullptr;
}

UCroActionComponent* UCAction::GetOwningComponent() const
{
	return Cast<UCroActionComponent>(GetOuter());
}

bool UCAction::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning())
	{
		return false;
	}

	UCroActionComponent* Comp = GetOwningComponent();

	if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}
	if (Instigator && Instigator->Implements<UCroActionInterface>())
	{
		float Mana = ICroActionInterface::Execute_GetCurrentMana(Instigator);
		if (ManaCost > Mana) 
		{
			return false;
		}
	}
	return true;
}

void UCAction::StartAction_Implementation(AActor* Instigator)
{
	if (ensure(Instigator))
	{
		UE_LOG(LogTemp, Log, TEXT("Running %s"), *GetNameSafe(this));

		UCroActionComponent* Comp = GetOwningComponent();
		Comp->ActiveGameplayTags.AppendTags(GrantsTags);

		if (ManaCost > 0)
		{
			if (ensure(Instigator->Implements<UCroActionInterface>()))
			{
				ICroActionInterface::Execute_UseMana(Instigator, ManaCost);
			}
		}

		bIsRunning = true;
	}
}

void UCAction::StopAction_Implementation(AActor* Instigator)
{
	if (ensure(Instigator))
	{
		UE_LOG(LogTemp, Log, TEXT("Stopped %s"), *GetNameSafe(this));

		ensureAlways(bIsRunning);

		UCroActionComponent* Comp = GetOwningComponent();
		Comp->ActiveGameplayTags.RemoveTags(GrantsTags);

		bIsRunning = false;
	}
}
