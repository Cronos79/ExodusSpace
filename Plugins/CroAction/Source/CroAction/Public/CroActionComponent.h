// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CAction.h"
#include "CroActionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CROACTION_API UCroActionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<UCAction*> Actions;
	UPROPERTY(EditAnywhere, Category = "Action")
	TArray<TSubclassOf<UCAction>> DefaultActions;

public:	
	// Sets default values for this component's properties
	UCroActionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Action")
	void AddAction(TSubclassOf<UCAction> ActionClass);
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StartActionByName(AActor* Instigator, FName ActionName);
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StopActionByName(AActor* Instigator, FName ActionName);
};
