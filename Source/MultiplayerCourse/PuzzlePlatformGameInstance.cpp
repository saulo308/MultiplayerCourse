// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuBase.h"
#include "MenuSystem/MainMenu.h"

const static FName SESSION_NAME = NAME_GameSession;
const static FName SERVER_NAME_SETTINGS_KEY = TEXT("ServerName");

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance() {
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuMainClassBP(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MenuMainClassBP.Class) 
		MenuClass = MenuMainClassBP.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> GameMenuClassBP(TEXT("/Game/MenuSystem/WBP_GameMenu"));
	if (GameMenuClassBP.Class) 
		GameMenuClass = GameMenuClassBP.Class;
}

void UPuzzlePlatformGameInstance::Init() {
	Super::Init();

	//Getting OnlineSubsystem Interface
	OSSInterface = IOnlineSubsystem::Get();
	//Getting SessionInterface and biding delegates
	SessionInterface = OSSInterface->GetSessionInterface();
	SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::CreateSessionComplete);
	SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::DestroySessionComplete);
	SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::FindSessionComplete);
	SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::JoinSessionComplete);

	UE_LOG(LogTemp, Warning, TEXT("Found substystem:%s"), *OSSInterface->GetSubsystemName().ToString());
}

void UPuzzlePlatformGameInstance::LoadMenu() {
	auto PlayerController = GetFirstLocalPlayerController();
	if (!MenuClass || !PlayerController) return;

	//Creating widget and adding to viewport
	MenuWidget = CreateWidget<UMainMenu>(this, MenuClass);
	MenuWidget->SetMenuInterface(this);
	MenuWidget->Setup();
}

void UPuzzlePlatformGameInstance::LoadGameMenu() {
	auto PlayerController = GetFirstLocalPlayerController();
	if (!PlayerController) return;

	//Creating game menu widget
	auto GameMenuWidget = CreateWidget<UMenuBase>(this, GameMenuClass);
	GameMenuWidget->SetMenuInterface(this);
	GameMenuWidget->Setup();
}

void UPuzzlePlatformGameInstance::HostServer(const FString& ServerName) {
	if (!SessionInterface.IsValid()) return;
	ServerCreationName = ServerName;

	//If there's a session openned already, destroy it
	if (SessionInterface->GetNamedSession(SESSION_NAME)) {
		SessionInterface->DestroySession(SESSION_NAME);
		return;
	}
	
	//If there's no existing sessiong, just create a new session
	CreateSession();
}

void UPuzzlePlatformGameInstance::CreateSession() {
	if (!SessionInterface.IsValid()) return;

	//Creating a session
	FOnlineSessionSettings OnlineSessionSettings;
	OnlineSessionSettings.bIsLANMatch = (OSSInterface->GetSubsystemName().IsEqual("NULL")) ? true : false;
	OnlineSessionSettings.NumPublicConnections = 2;
	OnlineSessionSettings.bShouldAdvertise = true;
	OnlineSessionSettings.bUsesPresence = true;
	OnlineSessionSettings.Set(SERVER_NAME_SETTINGS_KEY, ServerCreationName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	SessionInterface->CreateSession(0, SESSION_NAME, OnlineSessionSettings);
}

void UPuzzlePlatformGameInstance::JoinServer(uint32 ServerIndex) {
	if (!SessionInterface || !SessionSearch) return;
	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[ServerIndex]);
}

void UPuzzlePlatformGameInstance::BackToMainMenu() {
	auto PlayerController = GetFirstLocalPlayerController();
	PlayerController->ClientTravel(TEXT("/Game/Maps/MainMenuLevel"), ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformGameInstance::CreateSessionComplete(FName SessionName, bool bIsSuccess) {
	if (!bIsSuccess) {
		UE_LOG(LogTemp, Error, TEXT("Session %s could not be created!"), *SessionName.ToString());
		return;
	}

	//Travelling to server
	auto Engine = GetEngine();
	auto World = GetWorld();
	if (!Engine || !World) return;

	Engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Host successful!"));
	World->ServerTravel(TEXT("/Game/Maps/Lobby?listen"));
}

void UPuzzlePlatformGameInstance::DestroySessionComplete(FName SessionName, bool bIsSuccess) {
	if (!bIsSuccess) {
		UE_LOG(LogTemp, Error, TEXT("Session %s could not be destroyed!"), *SessionName.ToString());
		return;
	}

	//If we successfully destroyed existing session, then create a new one
	CreateSession();
}

void UPuzzlePlatformGameInstance::FindSessionComplete(bool bIsSuccess) {
	if (!bIsSuccess || !SessionInterface || !MenuWidget) {
		UE_LOG(LogTemp, Error, TEXT("Sessions could not be found!"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Session Search complete!"));
	//Server names storage
	TArray<FServerData> SeversData;

	//Getting sessions found
	//FServerData NewServerDataTest;
	//NewServerDataTest.ServerName = "Test Server 1";
	//SeversData.Add(NewServerDataTest);
	//NewServerDataTest.ServerName = "Test Server 2";
	//SeversData.Add(NewServerDataTest);
	//NewServerDataTest.ServerName = "Test Server 3";
	//SeversData.Add(NewServerDataTest);
	TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
	for (const auto Result : SearchResults) {
		auto SessionInfo = Result.Session;

		//Creating new ServerData
		FServerData NewServerData;
		FString ServerName;
		NewServerData.ServerName = (SessionInfo.SessionSettings.Get(SERVER_NAME_SETTINGS_KEY, ServerName)) ? ServerName : "Undefined Session";
		NewServerData.HostName = SessionInfo.OwningUserName;
		NewServerData.MaxConnectedPlayerNum = SessionInfo.SessionSettings.NumPublicConnections;
		NewServerData.CurConnectedPlayerNum = NewServerData.MaxConnectedPlayerNum - SessionInfo.NumOpenPublicConnections;

		//Adding to array
		SeversData.Add(NewServerData);
	}

	//Setting Menu server list
	MenuWidget->SetServerList(SeversData);
}

void UPuzzlePlatformGameInstance::RequestServerListRefresh() {
	//Finding all sessions
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("Start finding sessions!"));
		//SessionSearch->bIsLanQuery = true;
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE,true,EOnlineComparisonOp::Equals);
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UPuzzlePlatformGameInstance::JoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result) {
	if (!Result == EOnJoinSessionCompleteResult::Success) return;
	auto Engine = GetEngine();
	auto PlayerController = GetFirstLocalPlayerController();
	if (!Engine || !PlayerController) return;

	//Getting resolved string to connect
	FString ConnectInfo;
	bool bCanJoin = SessionInterface->GetResolvedConnectString(SessionName, ConnectInfo);
	if (!bCanJoin) return;

	//Connecting player
	Engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, FString::Printf(TEXT("Joining")));
	PlayerController->ClientTravel(ConnectInfo, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformGameInstance::StartSession() {
	//Travelling
	GetWorld()->ServerTravel(TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen"));
	if(SessionInterface)
		SessionInterface->StartSession(SESSION_NAME);
}