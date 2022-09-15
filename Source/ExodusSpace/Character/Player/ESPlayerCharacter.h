// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "../ESCharacter.h"
#include "ESPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/// <summary>
/// Player Character class
/// </summary>
UCLASS()
class EXODUSSPACE_API AESPlayerCharacter : public AESCharacter
{
	GENERATED_BODY()

protected:
	/// <summary>
	/// Components
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;

public:
	AESPlayerCharacter();

	/// <summary>
	/// Character Movement methods
	/// </summary>
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	void MoveForward(float Value);
	UFUNCTION()
	void MoveRight(float Value);
	UFUNCTION()
	void Turn(float Value);
	UFUNCTION()
	void LookUp(float Value);
};
