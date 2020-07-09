// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuBase.h"

const static FName SESSION_NAME = TEXT("My Game Session");

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

	//Finding sessions==TEMP==
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("Start finding sessions!"));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UPuzzlePlatformGameInstance::LoadMenu() {
	auto PlayerController = GetFirstLocalPlayerController();
	if (!MenuClass || !PlayerController) return;

	//Creating widget and adding to viewport
	auto MenuWidget = CreateWidget<UMenuBase>(this, MenuClass);
	MenuWidget->SetMenuInterface(this);
	MenuWidget->Setup();
}

void UPuzzlePlatformGameInstance::LoadGameMenu() {
	auto PlayerController = GetFirstLocalPlayerController();
	if (!PlayerController) return;

	//Creating game menu widget
	auto MenuWidget = CreateWidget<UMenuBase>(this, GameMenuClass);
	MenuWidget->SetMenuInterface(this);
	MenuWidget->Setup();
}

void UPuzzlePlatformGameInstance::HostServer() {
	if (!SessionInterface.IsValid()) return;

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
	SessionInterface->CreateSession(0, SESSION_NAME, OnlineSessionSettings);
}

void UPuzzlePlatformGameInstance::JoinServer(const FString& Address) {
	auto Engine = GetEngine();
	auto PlayerController = GetFirstLocalPlayerController();
	if (!Engine || !PlayerController) return;

	Engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
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
	World->ServerTravel(TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen"));
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
	if (!bIsSuccess) {
		UE_LOG(LogTemp, Error, TEXT("Sessions could not be found!"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Complete finding sessions!"));
}