// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CroItem.generated.h"

/**
 * 
 */
UCLASS()
class CROINVENTORY_API UCroItem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory")
	FName ItemName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory")
	FString ItemDesc;
};
