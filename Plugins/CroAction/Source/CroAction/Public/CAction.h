// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <GameplayTagContainer.h>
#include "CAction.generated.h"

class UCroActionComponent;

/**
 * 
 */
UCLASS(Blueprintable)
class CROACTION_API UCAction : public UObject
{
	GENERATED_BODY()
	
public:
	/* Action name to start and stop actions */
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	float ManaCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Action")
	bool bAutoStart{false};

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	FGameplayTagContainer GrantsTags;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	FGameplayTagContainer BlockedTags;

	UPROPERTY(ReplicatedUsing="OnRep_IsRunning")
	bool bIsRunning{ false };

	UPROPERTY(Replicated)
	UCroActionComponent* ActionComp;

	UPROPERTY(Replicated)
	AActor* ActionInstigator;

	UFUNCTION()
	void OnRep_IsRunning();

public:
	UFUNCTION()
	void InitializeAction(UCroActionComponent* NewActionComp);
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRunning() const;
	UWorld* GetWorld() const override;
	UFUNCTION(BlueprintCallable, Category = "Action")
	UCroActionComponent* GetOwningComponent() const;

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* Instigator);

	bool IsSupportedForNetworking() const override { return true; };
};
