// © 2022 CronoGames


#include "ESGameModeBase.h"
#include "../Character/Player/ESPlayerController.h"
#include "../Character/Player/ESPlayerCharacter.h"

void AESGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AESPlayerController* ESPC = Cast<AESPlayerController>(NewPlayer);

	if (ESPC)
	{
		TSubclassOf<AActor> SelectedClass = nullptr;
		for (FPlayerClasses PClass : ESPC->GetPlayerClasses())
		{
			if (PClass.ClassName == ESPC->PlayerClassName)
			{
				SelectedClass = PClass.CharClass;
				break;
			}
		}

		if (SelectedClass)
		{
			FActorSpawnParameters params;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FTransform Tr = ESPC->GetSpawnTransform();
			AESPlayerCharacter* NewChar =  Cast<AESPlayerCharacter>(GetWorld()->SpawnActor(SelectedClass, &Tr, params));
			if (NewChar)
			{
				NewChar->MyPlayerController = ESPC;
				ESPC->Possess(Cast<APawn>(NewChar));	
				//if (GEngine)
				//{
				//	FString Msg = FString::Printf(TEXT("[%s] Possed [%s]"), *GetNameSafe(ESPC), *GetNameSafe(NewChar));
				//	GEngine->AddOnScreenDebugMessage(-1, 45.0f, FColor::Red, Msg);
				//}
			}
		}
	}
}

void AESGameModeBase::SaveGame()
{

}

void AESGameModeBase::LoadGame()
{

}
