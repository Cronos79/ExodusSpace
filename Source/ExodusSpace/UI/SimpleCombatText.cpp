// © 2022 CronoGames


#include "SimpleCombatText.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetTextLibrary.h"

void USimpleCombatText::PlayCombatText(float Damage)
{
	if (FloatingTextAnimation)
	{
		const int32 DamageToShow = UKismetMathLibrary::Round(Damage);
		const FText TextDamage = UKismetTextLibrary::Conv_IntToText(DamageToShow);
		DamageText->SetText(TextDamage);
		PlayAnimation(FloatingTextAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
	}
}
