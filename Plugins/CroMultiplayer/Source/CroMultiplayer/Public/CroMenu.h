// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Interfaces/OnlineSessionInterface.h>
#include "CroMenu.generated.h"

class UButton;
class UMultiplayerSessionsSubsystem;

/**
 * 
 */
UCLASS()
class CROMULTIPLAYER_API UCroMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 LocalNumPublicPlayers = 4, FString LocalMatchType = TEXT("FreeForAll"), FString LobbyPath = TEXT("/Game/Maps/Lobby"));

protected:

	virtual bool Initialize() override;
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

/// <summary>
/// Callbacks for the multiplayer sessions
/// </summary>
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	//UFUNCTION()
	void OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResult, bool bWasSuccessful);
	//UFUNCTION()
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);


private:
	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;
	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UFUNCTION()
	void JoinButtonClicked();
	UFUNCTION()
	void HostButtonClicked();

	void MenuTearDown();

	UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

	int32 NumPublicPlayers{4};
	FString MatchType{TEXT("FreeForAll")};
	FString PathToLobby{ TEXT("") };
};
