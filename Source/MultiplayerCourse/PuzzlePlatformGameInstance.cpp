// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuBase.h"
#include "OnlineSubsystem.h"

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

	//OnlineSubsystem Interface
	auto OSSInterface = IOnlineSubsystem::Get();
	if (!OSSInterface) return;

	auto SessionInterface = OSSInterface->GetSessionInterface();
	if (!SessionInterface.IsValid()) return;

	UE_LOG(LogTemp, Warning, TEXT("Interface name:%s and found Session Interface"), *OSSInterface->GetSubsystemName().ToString());
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
	auto Engine = GetEngine();
	auto World = GetWorld();
	if (!Engine || !World) return;

	Engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Host successful!"));
	World->ServerTravel(TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen"));
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