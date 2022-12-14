// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "CAction.h"
#include "CAction_ProjectileAttack.generated.h"

/**
 * 
 */
UCLASS()
class EXODUSSPACE_API UCAction_ProjectileAttack : public UCAction
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Action")
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(VisibleAnywhere, Category = "Action")
	FName HandSocketName;
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	float AttackAnimDelay;
	UPROPERTY(EditAnywhere, Category = "Action")
	UAnimMontage* AttackAnim;

public:
	UCAction_ProjectileAttack();

	virtual void StartAction_Implementation(AActor* Instigator) override;

protected:
	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigaterCharacter);
};
