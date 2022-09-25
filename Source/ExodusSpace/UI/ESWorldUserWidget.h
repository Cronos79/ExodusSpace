// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ESWorldUserWidget.generated.h"

class USizeBox;

/**
 * 
 */
UCLASS()
class EXODUSSPACE_API UESWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;

public:
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	AActor* AttachedActor;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
