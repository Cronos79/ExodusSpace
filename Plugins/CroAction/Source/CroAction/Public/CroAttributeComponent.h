// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Delegates/DelegateCombinations.h>
#include "CroAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnHealthChanged, AActor*, InstigatorActor, UCroAttributeComponent*, OwningComp, float, NewHealth, float, MaxHealth, float, ChangedAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnManaChanged, AActor*, InstigatorActor, UCroAttributeComponent*, OwningComp, float, NewMana, float, MaxMana, float, ChangedAmount);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CROACTION_API UCroAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	FString ToonName{ "DefaultName" };
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	float MaxHealth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Mana;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	float MaxMana;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	int32 ToonLevel{1};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	int32 Vitality{10};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	int32 Intelligence{10};

	/*
	Things to add
	Strength - carry weight max / damage
	Agility - Rest decay rate / damage
	Hunger
	Thirst
	Rest
	BaseDamage
	CarryWeightMax
	*/

public:
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnHealthChanged OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnManaChanged OnManaChanged;

public:	
	// Sets default values for this component's properties
	UCroAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void SetPlayerName(FString NewName);
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsAlive();
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool Heal(float Value, AActor* OtherActor);
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool TakeDamage(float Value, AActor* OtherActor);
	UFUNCTION()
	void HandleDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool HasEnoughMana(float Value);
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool GainMana(float Value);
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool UseMana(float Value);

protected:
	UFUNCTION()
	bool ApplyHealthChange(float Value, AActor* OtherActor);
	UFUNCTION()
	bool ApplyManaChange(float Value);
};
