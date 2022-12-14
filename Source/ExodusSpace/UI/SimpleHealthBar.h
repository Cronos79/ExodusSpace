// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/Components/ProgressBar.h"
#include "SimpleHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class EXODUSSPACE_API USimpleHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Attribute", meta = (BindWidget))
	UProgressBar* HealthBar;
};
