// © 2022 CronoGames


#include "ESPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>
#include "CroActionComponent.h"
#include "../../Components/ESInteractionComponent.h"

AESPlayerCharacter::AESPlayerCharacter()
{
	// Components
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	InteractionComp = CreateDefaultSubobject<UESInteractionComponent>(TEXT("Interaction comp"));
	
	// Movement
	bUseControllerRotationYaw = true;
	SpringArmComp->bUsePawnControlRotation = true;
}

FVector AESPlayerCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}

UCameraComponent* AESPlayerCharacter::GetMainCamera()
{
	return CameraComp;
}

bool AESPlayerCharacter::CameraLineTrace(float TraceDistance, FHitResult &OutHit, ECollisionChannel TraceChannel, bool ShowDebug)
{
	FVector TraceStart = CameraComp->GetComponentLocation();;
	FVector TraceEnd = TraceStart + (CameraComp->GetForwardVector() * TraceDistance);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult Hit;
	bool BlockingHit = GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannel, Params);
		
	if (ShowDebug)
	{
		FColor LineColor = BlockingHit ? FColor::Green : FColor::Red;
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, LineColor, false, 2.0f, 0, 2.0f);
	}
	OutHit = Hit;
	return BlockingHit;
}

/********************************************************************** Movement **********************************************************************/
void AESPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AESPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AESPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AESPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AESPlayerCharacter::LookUp);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AESPlayerCharacter::Interact);

	// Actions
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AESPlayerCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AESPlayerCharacter::SprintStop);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AESPlayerCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &AESPlayerCharacter::SecondaryAttack);

	PlayerInputComponent->BindAction("SkillOne", IE_Pressed, this, &AESPlayerCharacter::SkillOne);
	PlayerInputComponent->BindAction("SkillTwo", IE_Pressed, this, &AESPlayerCharacter::SkillTwo);
	PlayerInputComponent->BindAction("SkillThree", IE_Pressed, this, &AESPlayerCharacter::SkillThree);
	PlayerInputComponent->BindAction("SkillFour", IE_Pressed, this, &AESPlayerCharacter::SkillFour);

}

void AESPlayerCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector(), Value);
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
/********************************************************************* End Movement ********************************************************************/
void AESPlayerCharacter::Interact()
{
	UE_LOG(LogTemp, Log, TEXT("Interact clicked"));
	InteractionComp->Interact();
}
