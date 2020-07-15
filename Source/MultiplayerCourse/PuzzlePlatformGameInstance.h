// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"

#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERCOURSE_API UPuzzlePlatformGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformGameInstance();
	virtual void Init() override;

	//Exec functions
	UFUNCTION(Exec,BlueprintCallable)
	void LoadMenu();
	UFUNCTION(Exec)
	void LoadGameMenu();

	UFUNCTION(Exec)
	virtual void HostServer() override;
	UFUNCTION(Exec)
	virtual void JoinServer(uint32 ServerIndex) override;
	UFUNCTION(Exec)
	virtual void BackToMainMenu() override;
	virtual void RequestServerListRefresh() override;

protected:
	void JoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void CreateSessionComplete(FName SessionName, bool bIsSuccess);
	void DestroySessionComplete(FName SessionName, bool bIsSuccess);
	void FindSessionComplete(bool bIsSuccess);
	void CreateSession();

protected:
	UPROPERTY()
	TSubclassOf<UUserWidget> MenuClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> GameMenuClass;
	UPROPERTY()
	class UMainMenu* MenuWidget = nullptr;

	//OnlineSubsystemInterfaces and variables
	IOnlineSubsystem* OSSInterface = nullptr;
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
