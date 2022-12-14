// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CroItem.generated.h"

UENUM(BlueprintType)
enum class EInventorySlotType : uint8 {
	Any			UMETA(DisplayName = "Any"),
	MainHand	UMETA(DisplayName = "MainHand"),
	OffHand		UMETA(DisplayName = "OffHand"),
	Helm		UMETA(DisplayName = "Helm"),
	Shoulder	UMETA(DisplayName = "Shoulder"),
	Chest		UMETA(DisplayName = "Chest"),
	Gloves		UMETA(DisplayName = "Gloves"),
	Bracers		UMETA(DisplayName = "Bracers"),
	Belt		UMETA(DisplayName = "Belt"),
	Legs		UMETA(DisplayName = "Legs"),
	Boots		UMETA(DisplayName = "Boots"),
	Neck		UMETA(DisplayName = "Neck"),
	LeftRing	UMETA(DisplayName = "LeftRing"),
	RightRing	UMETA(DisplayName = "RightRing")
};

/**
 * 
 */
UCLASS()
class CROINVENTORY_API UCroItem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory")
	EInventorySlotType ItemType;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory")
	FName ItemName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory")
	FString ItemDesc;

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InitItem(EInventorySlotType NewItemType, FName NewItemName, FString NewItemDesc);
};
