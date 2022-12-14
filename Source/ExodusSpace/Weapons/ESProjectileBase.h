// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ESProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(ABSTRACT)
class EXODUSSPACE_API AESProjectileBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* MoveComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	float Damage{20.0f};
public:	
	// Sets default values for this actor's properties
	AESProjectileBase();

protected:
	virtual void PostInitializeComponents() override;

	// 'virtual' so we can override this in child-classes
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Projectile")
	void OnHit(AActor* HitActor);
};
