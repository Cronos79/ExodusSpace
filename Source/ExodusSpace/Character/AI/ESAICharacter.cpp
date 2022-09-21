// © 2022 CronoGames


#include "ESAICharacter.h"
#include "CroActionComponent.h"

void AESAICharacter::PrimaryAttack()
{
	ActionComp->StartActionByName(this, "PrimaryAttack");
}
