// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ESCharacter.generated.h"

class UCroAttributeComponent;
class UCroActionComponent;

UCLASS()
class EXODUSSPACE_API AESCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCroAttributeComponent* AttributeComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCroActionComponent* ActionComp;

public:
	// Sets default values for this character's properties
	AESCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
