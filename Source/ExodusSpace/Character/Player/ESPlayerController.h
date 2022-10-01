// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <Delegates/DelegateCombinations.h>
#include "ESPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnChanged, APawn*, NewPawn);

USTRUCT(BlueprintType)
struct FPlayerClasses
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ClassName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> CharClass;
};

/**
 * 
 */
UCLASS()
class EXODUSSPACE_API AESPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "PlayerClass")
	TArray<FPlayerClasses> PlayerClassOptions;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerClass")
	FString PlayerClassName;
public:
	FOnPawnChanged OnPawnChanged;
	void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	TArray<FPlayerClasses> GetPlayerClasses();
	UFUNCTION()
	FTransform GetSpawnTransform();
};
