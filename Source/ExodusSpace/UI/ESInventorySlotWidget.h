// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Delegates/DelegateCombinations.h"
#include <CroItem.h>
#include "ESInventorySlotWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlotHovered, EInventorySlotType, Type, int32, InventoryIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlotUnHovered);

/**
 * 
 */
UCLASS()
class EXODUSSPACE_API UESInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 SlotIndex;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	class UButton* SlotButton;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	class UImage* SlotImage;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	class UBorder* AmountBorder;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	class UTextBlock* AmountText;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (ExposeOnSpawn = "true"))
	EInventorySlotType SlotType;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnSlotHovered OnHovered;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnSlotUnHovered OnUnHovered;

protected:
	bool Initialize() override;

	void NativeConstruct() override;
	void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;
	void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;

	UFUNCTION()
	void OnSlotClicked();
	UFUNCTION()
	void OnSlotHovered();
	UFUNCTION()
	void OnSlotUnHovered();

public:
	UFUNCTION()
	void SetImageVisibility();
	UFUNCTION()
	void SetDefaultStyle();
	UFUNCTION()
	void SetActiveStyle();
	UFUNCTION()
	void SetSlotType(EInventorySlotType Type);
};
