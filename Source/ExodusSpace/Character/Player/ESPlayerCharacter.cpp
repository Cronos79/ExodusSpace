// © 2022 CronoGames


#include "ESPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>

AESPlayerCharacter::AESPlayerCharacter()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	
}

void AESPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AESPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AESPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AESPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AESPlayerCharacter::LookUp);
}

void AESPlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AESPlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AESPlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AESPlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(-Value);
}
