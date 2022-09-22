// © 2022 CronoGames


#include "ESGameStateBase.h"
#include <Kismet/KismetMathLibrary.h>

void AESGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	GameSpeed = 4;
	Year = 1245;
	Month = 3;
	Day = 15;
	Hours = 5;
	GetWorldTimerManager().SetTimer(ClockTimerHandle, this, &AESGameStateBase::UpdateClock, 1.0f / 60.0f, true, 0.0f);
}

void AESGameStateBase::UpdateClock()
{
	TotalSecondsInDay = TotalSecondsInDay + GameSpeed;
	FTimespan timeSpan = UKismetMathLibrary::MakeTimespan(0, 0, 0, TotalSecondsInDay, 0);
	Seconds = timeSpan.GetSeconds();
	Minutes = timeSpan.GetMinutes();
	Hours = timeSpan.GetHours();

	if (TotalSecondsInDay >= 86400)
	{
		TotalSecondsInDay = 0;
		Day++;
	}

	int32 daysInMonth = UKismetMathLibrary::DaysInMonth(Year, Month);

	if (Day > daysInMonth)
	{
		Day = 1;
		Month++;
	}

	if (Month > 12)
	{
		Month = 1;
		Year++;
	}
	Calendar = UKismetMathLibrary::MakeDateTime(Year, Month, Day, Hours, Minutes, Seconds);
}
