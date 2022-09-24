// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Delegates/DelegateCombinations.h>
#include <CroActionInterface.h>
#include "ESCharacter.generated.h"

class UCroAttributeComponent;
class UCroActionComponent;
class UWidgetComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreditsChanged, int32, NewCredits);

UCLASS()
class EXODUSSPACE_API AESCharacter : public ACharacter, public ICroActionInterface
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	int32 Credits{ 0 };

public:
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnCreditsChanged OnCreditsChanged;

	// Actions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	FName PrimaryAttackName{ "PrimaryAttack" };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	FName SecondaryAttackName{ "SecondaryAttack" };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	FName SkillOneName{ "SkillOne" };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	FName SkillTwoName{ "SkillTwo" };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	FName SkillThreeName{ "SkillThree" };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	FName SkillFourName{ "SkillFour" };

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

	UFUNCTION(BlueprintCallable, Category = "Items")
	void GainCredits(int32 Value);
	UFUNCTION(BlueprintCallable, Category = "Items")
	bool SpendCredits(int32 Value);

	virtual bool UseMana_Implementation(float Amount) override;
	virtual float GetCurrentMana_Implementation() override;
	virtual bool HasEnoughMana_Implementation(float Amount) override;
};
