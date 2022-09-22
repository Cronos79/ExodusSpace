// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ESGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class EXODUSSPACE_API AESGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
protected:
	FTimerHandle ClockTimerHandle;
	int32 TotalSecondsInDay;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Time")
	int32 Seconds;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Time")
	int32 Minutes;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Time")
	int32 Hours;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Time")
	int32 Day;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Time")
	int32 Month;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Time")
	int32 Year;
	UPROPERTY(BlueprintReadOnly, Category = "Time")
	FDateTime Calendar;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Time")
	int32 GameSpeed;
protected:
	virtual void BeginPlay() override;
	void UpdateClock();
};
