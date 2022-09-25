// © 2022 CronoGames


#include "CroAttributeComponent.h"
#include <GameFramework/Character.h>
#include "GameFramework/PlayerState.h"
#include <Net/UnrealNetwork.h>

// Sets default values for this component's properties
UCroAttributeComponent::UCroAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = Vitality * 10.0f;
	Health = MaxHealth;
	MaxMana = Intelligence * 5.0f;
	Mana = MaxMana;

	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void UCroAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UCroAttributeComponent::HandleDamage);
	}
}

void UCroAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCroAttributeComponent, ToonName);
	DOREPLIFETIME(UCroAttributeComponent, Health);
	DOREPLIFETIME(UCroAttributeComponent, MaxHealth);
}

void UCroAttributeComponent::SetPlayerName(FString NewName)
{
	//AActor* Owner = GetOwner(); // #TODO: Fix player name when we do a database
	//if (Owner)
	//{
	//	ACharacter* PC = Cast<ACharacter>(Owner);
	//	if (PC)
	//	{
	//		APlayerState* PS = PC->GetPlayerState();
	//		if (PS)
	//		{
	//			ToonName = PS->GetPlayerName();
	//		}
	//	}
	//}
	ToonName = NewName;
}

bool UCroAttributeComponent::IsAlive()
{
	return Health > 0.0f;
}

bool UCroAttributeComponent::Heal(float Value, AActor* OtherActor)
{
	if (!IsAlive())
	{
		return false;
	}
	return ApplyHealthChange(Value, OtherActor);
}

bool UCroAttributeComponent::TakeDamage(float Value, AActor* OtherActor)
{
	return ApplyHealthChange(-Value, OtherActor);
}


void UCroAttributeComponent::HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	TakeDamage(Damage, DamageCauser);
}

bool UCroAttributeComponent::HasEnoughMana(float Value)
{
	return Mana >= Value;
}

bool UCroAttributeComponent::GainMana(float Value)
{
	return ApplyManaChange(Value);
}

bool UCroAttributeComponent::UseMana(float Value)
{
	if (!HasEnoughMana(Value))
	{
		return false;
	}
	return ApplyManaChange(-Value);
}

float UCroAttributeComponent::GetMana()
{
	return Mana;
}

bool UCroAttributeComponent::ApplyHealthChange(float Value, AActor* OtherActor)
{
	float OldHealth = Health;
	Health = FMath::Clamp(Health + Value, 0.0f, MaxHealth);
	float NewValue = Health - OldHealth;
	if (NewValue != 0.0f)
	{
		MulticastHealthChanged(OtherActor, this, Health, MaxHealth, NewValue);
	}
	return true;
}

void UCroAttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, UCroAttributeComponent* Comp, float NewHealth, float NewMaxHealth, float ChangedAmount)
{
	OnHealthChanged.Broadcast(InstigatorActor, Comp, NewHealth, NewMaxHealth, ChangedAmount);
}

bool UCroAttributeComponent::ApplyManaChange(float Value)
{
	Mana = FMath::Clamp(Mana + Value, 0.0f, MaxMana);
	OnManaChanged.Broadcast(nullptr, this, Mana, MaxMana, Value);
	return true;
}

