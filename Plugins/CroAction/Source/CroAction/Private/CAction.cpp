// © 2022 CronoGames


#include "CAction.h"
#include <CroActionComponent.h>
#include <CroActionInterface.h>
#include "Net/UnrealNetwork.h"

void UCAction::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCAction, RepData);
	DOREPLIFETIME(UCAction, ActionComp);
}

void UCAction::OnRep_RepData()
{
	if (RepData.bIsRunning)
	{
		StartAction(RepData.ActionInstigator);
	}
	else
	{
		StopAction(RepData.ActionInstigator);
	}
}

void UCAction::InitializeAction(UCroActionComponent* NewActionComp)
{
	ActionComp = NewActionComp;
}

bool UCAction::IsRunning() const
{
	return RepData.bIsRunning;
}

UWorld* UCAction::GetWorld() const
{
	if (RepData.ActionInstigator)
	{
		return RepData.ActionInstigator->GetWorld();
	}
	AActor* Actor = Cast<AActor>(GetOuter());
	if (Actor)
	{
		return Actor->GetWorld();
	}
	return nullptr;
}

UCroActionComponent* UCAction::GetOwningComponent() const
{
	return ActionComp;
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
	RepData.ActionInstigator = Instigator;
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

		RepData.bIsRunning = true;
	}
}

void UCAction::StopAction_Implementation(AActor* Instigator)
{
	if (ensure(Instigator))
	{
		UE_LOG(LogTemp, Log, TEXT("Stopped %s"), *GetNameSafe(this));

		//ensureAlways(bIsRunning);

		UCroActionComponent* Comp = GetOwningComponent();
		Comp->ActiveGameplayTags.RemoveTags(GrantsTags);

		RepData.bIsRunning = false;
	}
}
