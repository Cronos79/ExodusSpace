// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ESCharacterInfoWidget.generated.h"

class UESInventorySlotWidget;

/**
 * 
 */
UCLASS()
class EXODUSSPACE_API UESCharacterInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	UESInventorySlotWidget* HeadSlot;
	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	UESInventorySlotWidget* ShoulderSlot;
	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	UESInventorySlotWidget* ChestSlot;
	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	UESInventorySlotWidget* GlovesSlot;
	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	UESInventorySlotWidget* BracersSlot;
	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	UESInventorySlotWidget* BeltSlot;
	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	UESInventorySlotWidget* LegsSlot;
	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	UESInventorySlotWidget* BootsSlot;
	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	UESInventorySlotWidget* NeckSlot;
	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	UESInventorySlotWidget* LeftRingSlot;
	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	UESInventorySlotWidget* RightRingSlot;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	UESInventorySlotWidget* MainHandSlot;
	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (BindWidget))
	UESInventorySlotWidget* OffHandSlot;

public:
	bool Initialize() override;
};
