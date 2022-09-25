// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ESInteractionComponent.generated.h"

class UESWorldUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXODUSSPACE_API UESInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	AActor* HitActor;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UESWorldUserWidget> DefaultWidgetClass;

	UPROPERTY()
	UESWorldUserWidget* DefaultWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float TraceDistance{1000};

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TEnumAsByte<ECollisionChannel> CollisionChannel{ECC_Visibility};

public:	
	// Sets default values for this component's properties
	UESInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION()
	void FindInteractable();
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void Interact();
	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor* InFocus);
};
