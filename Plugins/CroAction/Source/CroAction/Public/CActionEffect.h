// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "CAction.h"
#include "CActionEffect.generated.h"

/**
 * 
 */
UCLASS()
class CROACTION_API UCActionEffect : public UCAction
{
	GENERATED_BODY()

public:
	UCActionEffect();

	void StartAction_Implementation(AActor* Instigator) override;

	void StopAction_Implementation(AActor* Instigator) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	float Duration;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	float Period;

	FTimerHandle DurationHandle;
	FTimerHandle PeriodHandle;

	UFUNCTION(BlueprintNativeEvent, Category = "Effect")
	void ExecutePeriodicEffect(AActor* Instigator);
	
};
