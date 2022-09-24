// © 2022 CronoGames


#include "CroActionComponent.h"

// Sets default values for this component's properties
UCroActionComponent::UCroActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCroActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UCAction> ActionClass : DefaultActions)
	{
		AddAction(GetOwner(), ActionClass);
	}
	
}


// Called every frame
void UCroActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GEngine)
	{
		FString DebugMsg = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Cyan, DebugMsg);
	}
}

void UCroActionComponent::RemoveAction(UCAction* ActionToRemove)
{
	if (!ensure(ActionToRemove && !ActionToRemove->IsRunning()))
	{
		return;
	}
	Actions.Remove(ActionToRemove);
}

void UCroActionComponent::AddAction(AActor* Instigator, TSubclassOf<UCAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	UCAction* NewAction = NewObject<UCAction>(this, ActionClass);
	if (ensure(NewAction))
	{
		Actions.Add(NewAction);

		if (NewAction->bAutoStart && ensure(NewAction->CanStart(Instigator)))
		{
			NewAction->StartAction(Instigator);
		}
	}
}

bool UCroActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (UCAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (!Action->CanStart(Instigator))
			{
				FString FailedMsg = GetNameSafe(Instigator) + " : " + "Failed to run action: " + ActionName.ToString();
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FailedMsg);
				}
				continue;
			}
			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool UCroActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (UCAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->IsRunning())
			{
				Action->StopAction(Instigator);
				return true;
			}		
		}
	}
	return false;
}

