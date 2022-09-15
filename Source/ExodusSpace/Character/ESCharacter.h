// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ESCharacter.generated.h"

UCLASS()
class EXODUSSPACE_API AESCharacter : public ACharacter
{
	GENERATED_BODY()

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
