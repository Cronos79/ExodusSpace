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
		FVector HandLocation = InstigaterCharacter->GetActorLocation();
		HandLocation.Z += 64.0f;
		HandLocation.X += -40.0f;
		if (InstigaterCharacter->GetMesh()->GetSocketLocation(HandSocketName).IsZero() != true)
		{
			//HandLocation = InstigaterCharacter->GetMesh()->GetSocketLocation(HandSocketName); // #TODO: Set to skl mesh
		}
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
		FHitResult Hit;
		PC->CameraLineTrace(5000.0f, Hit);
		FVector HitPoint;
		if (Hit.bBlockingHit)
		{
			HitPoint = Hit.ImpactPoint;
		}
		else
		{
			HitPoint = Hit.TraceEnd;
		}
		FRotator ProjRotation = FRotationMatrix::MakeFromX(HitPoint - HandLocation).Rotator();

		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}

	StopAction(InstigaterCharacter);
}
