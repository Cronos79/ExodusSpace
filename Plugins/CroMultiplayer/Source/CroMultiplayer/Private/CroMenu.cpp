// Fill out your copyright notice in the Description page of Project Settings.


#include "CroMenu.h"
#include "Components/Button.h"
#include "MultiplayerSessionsSubsystem.h"
#include <OnlineSubsystem.h>

void UCroMenu::MenuSetup(int32 LocalNumPublicPlayers, FString LocalMatchType, FString LobbyPath)
{
	PathToLobby = LobbyPath;
	NumPublicPlayers = LocalNumPublicPlayers;
	MatchType = LocalMatchType;
	//AddToViewport(); // #NOTE: Adding parent to view port
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PC = World->GetFirstPlayerController();
		if (PC)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PC->SetInputMode(InputModeData);

			PC->SetShowMouseCursor(true);
		}
	}

	UGameInstance* GI = GetGameInstance();
	if (GI)
	{
		MultiplayerSessionsSubsystem = GI->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}

	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &UCroMenu::OnCreateSession);
		MultiplayerSessionsSubsystem->MultiplayerOnFindSessionComplete.AddUObject(this, &UCroMenu::OnFindSession);
		MultiplayerSessionsSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &UCroMenu::OnJoinSession);
		MultiplayerSessionsSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &UCroMenu::OnDestroySession);
		MultiplayerSessionsSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this, &UCroMenu::OnStartSession);
	}
}

bool UCroMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UCroMenu::JoinButtonClicked);
	}
	
	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &UCroMenu::HostButtonClicked);
	}

	return true;
}

void UCroMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{	
	MenuTearDown();
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}

void UCroMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FString NewPath = FString::Printf(TEXT("%s?listen"), *PathToLobby);
			World->ServerTravel(NewPath);
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString(TEXT("OnCreateSession FAILED")));
		}
		HostButton->SetIsEnabled(true);
	}
}

void UCroMenu::OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResult, bool bWasSuccessful)
{
	if (MultiplayerSessionsSubsystem == nullptr)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString(TEXT("Invalid MultiplayerSessionsSubsystem")));
		}
		return;
	}

	if (bWasSuccessful)
	{
		for (auto Result : SessionResult)
		{
			FString SettingsValue;
			Result.Session.SessionSettings.Get(FName("MatchType"), SettingsValue);
			if (SettingsValue == MatchType)
			{
				MultiplayerSessionsSubsystem->JoinSession(Result);
				return;
			}
		}
	}
	else
	{
		JoinButton->SetIsEnabled(true);
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString(TEXT("Didnt find session")));
	}
}

void UCroMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{	
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface)
		{
			FString Address;
			SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);
		/*	if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString(TEXT("SessionInterface Success")));
			}*/
			APlayerController* PC = GetGameInstance()->GetFirstLocalPlayerController();
			if (PC)
			{
				PC->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
			}
		}
	}
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		JoinButton->SetIsEnabled(true);
	}
}

void UCroMenu::OnDestroySession(bool bWasSuccessful)
{

}

void UCroMenu::OnStartSession(bool bWasSuccessful)
{

}

void UCroMenu::JoinButtonClicked()
{
	JoinButton->SetIsEnabled(false);
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->FindSessions(10000);
	}
}

void UCroMenu::HostButtonClicked()
{
	HostButton->SetIsEnabled(false);
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->CreateSession(NumPublicPlayers, MatchType);	
	}
}

void UCroMenu::MenuTearDown()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PC = World->GetFirstPlayerController();
		if (PC)
		{
			FInputModeGameOnly IMD;
			PC->SetInputMode(IMD); PC->SetShowMouseCursor(false);
		}
	}
}
