// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "ESProjectileBase.h"
#include <GameplayTagContainer.h>
#include <CAction.h>
#include "ESArcaneMissleProjectile.generated.h"

class USphereComponent;

/**
 * 
 */
UCLASS()
class EXODUSSPACE_API AESArcaneMissleProjectile : public AESProjectileBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FGameplayTag ParryTag;
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	TSubclassOf<UCAction> BurningActionClass;
public:
	AESArcaneMissleProjectile();

protected:
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
