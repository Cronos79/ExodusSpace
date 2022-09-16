// © 2022 CronoGames


#include "CAction_ProjectileAttack.h"
#include <GameFramework/Character.h>
#include "../Character/Player/ESPlayerCharacter.h"
#include <Camera/CameraComponent.h>

UCAction_ProjectileAttack::UCAction_ProjectileAttack()
{
	HandSocketName = "RHand";
	AttackAnimDelay = 0.2f;
}

void UCAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (Character)
	{
		Character->PlayAnimMontage(AttackAnim);

		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);
	}
}

void UCAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigaterCharacter)
{
	if (ensureAlways(ProjectileClass))
	{
		FVector HandLocation = InstigaterCharacter->GetMesh()->GetSocketLocation(HandSocketName);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigaterCharacter;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InstigaterCharacter);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);



		AESPlayerCharacter* PC = Cast<AESPlayerCharacter>(InstigaterCharacter);

		FVector TraceStart;
		FVector TraceEnd;
		if (PC)
		{
			TraceStart = PC->GetPawnViewLocation();
			TraceEnd = TraceStart + (PC->GetMainCamera()->GetForwardVector() * 5000);
		}
		else
		{
			TraceStart = InstigaterCharacter->GetPawnViewLocation();
			TraceEnd = TraceStart + (InstigaterCharacter->GetControlRotation().Vector() * 5000);
		}		

		FHitResult Hit;

		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			TraceEnd = Hit.ImpactPoint;
		}

		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();

		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}

	StopAction(InstigaterCharacter);
}
