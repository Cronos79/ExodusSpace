// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "../ESCharacter.h"
#include "ESPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class EXODUSSPACE_API AESPlayerCharacter : public AESCharacter
{
	GENERATED_BODY()

public:
	AESPlayerCharacter();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
