// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "../ESCharacter.h"
#include "ESPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UESInteractionComponent;

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
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UESInteractionComponent* InteractionComp;

public:
	AESPlayerCharacter();

	virtual FVector GetPawnViewLocation() const override;
	UCameraComponent* GetMainCamera();
	bool CameraLineTrace(float TraceDistance, FHitResult &Hit, ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility, bool ShowDebug = false);

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

	UFUNCTION()
	void Interact();
	/// <summary>
	/// Character CroAction methods
	/// </summary>
	UFUNCTION()
	void SprintStart();
	UFUNCTION()
	void SprintStop();
	UFUNCTION()
	void PrimaryAttack();
};
