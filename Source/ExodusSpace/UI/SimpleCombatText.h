// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "SimpleCombatText.generated.h"

/**
 * 
 */
UCLASS()
class EXODUSSPACE_API USimpleCombatText : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UTextBlock* DamageText;

	UPROPERTY(BlueprintReadWrite , Category = "UI")
	UWidgetAnimation* FloatingTextAnimation;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void PlayCombatText(float Damage);
};
