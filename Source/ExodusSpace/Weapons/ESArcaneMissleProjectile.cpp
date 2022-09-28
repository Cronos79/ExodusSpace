// © 2022 CronoGames


#include "ESArcaneMissleProjectile.h"
#include "Components/SphereComponent.h"
#include "CroActionComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/GameplayStatics.h>

AESArcaneMissleProjectile::AESArcaneMissleProjectile()
{
	SphereComp->SetSphereRadius(20.0f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AESArcaneMissleProjectile::OnActorOverlap);

	Damage = 20.0f;
}

void AESArcaneMissleProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UCroActionComponent* ActionComp = Cast<UCroActionComponent>(OtherActor->GetComponentByClass(UCroActionComponent::StaticClass()));
		if (ActionComp && ActionComp->ActiveGameplayTags.HasTag(ParryTag))
		{
			MoveComp->Velocity = -MoveComp->Velocity;

			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}
		
		if (UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigator()->GetController(), GetInstigator(), UDamageType::StaticClass()))
		{
			OnHit(OtherActor);

			if (ActionComp && HasAuthority())
			{
				ActionComp->AddAction(GetInstigator(), BurningActionClass);
			}
		}
	}
}
