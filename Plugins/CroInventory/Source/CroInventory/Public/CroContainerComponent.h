// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CroItem.h"
#include "CroContainerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CROINVENTORY_API UCroContainerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TArray<UCroItem*> Items;

public:	
	// Sets default values for this component's properties
	UCroContainerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
