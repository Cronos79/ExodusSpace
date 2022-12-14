// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/ESGamePlayInterface.h"
#include "ESItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class EXODUSSPACE_API AESItemChest : public AActor, public IESGamePlayInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "CItem")
		float TargetRoll{-110.0f};

protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* LidMesh;
	
public:	
	// Sets default values for this actor's properties
	AESItemChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void Interact_Implementation(APawn* InstigatorPawn);

};
