// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ESCharacter.generated.h"

class UCroAttributeComponent;
class UCroActionComponent;
class UWidgetComponent;

UCLASS()
class EXODUSSPACE_API AESCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCroAttributeComponent* AttributeComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCroActionComponent* ActionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HealthBar;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* CombatText;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthbarClass;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> CombatTextClass;

public:
	// Sets default values for this character's properties
	AESCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PossessedBy(AController* NewController) override;

public:
	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, UCroAttributeComponent* OwningComp, float NewHealth, float MaxHealth, float ChangedAmount);
	UFUNCTION()
	void UpdateHealthBar(float CurrentValue, float MaxValue);
};
