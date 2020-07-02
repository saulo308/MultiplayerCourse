// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance() {
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuMainClassBP(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MenuMainClassBP.Class) {
		MenuClass = MenuMainClassBP.Class;
		UE_LOG(LogTemp, Warning, TEXT("%s"),*MenuClass->GetName());
	}
}

void UPuzzlePlatformGameInstance::LoadMenu() {
	auto PlayerController = GetFirstLocalPlayerController();
	if (!MenuClass || !PlayerController) return;

	//Creating widget and addingo to viewport
	auto MenuWidget = CreateWidget<UMainMenu>(this, MenuClass);
	MenuWidget->SetMenuInterface(this);
	MenuWidget->Setup();
}

void UPuzzlePlatformGameInstance::Host() {
	auto Engine = GetEngine();
	auto World = GetWorld();
	if (!Engine || !World) return;

	Engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Host successful!"));
	World->ServerTravel(TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen"));
}

void UPuzzlePlatformGameInstance::Join(const FString& Address) {
	auto Engine = GetEngine();
	auto PlayerController = GetFirstLocalPlayerController();
	if (!Engine) return;

	Engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformGameInstance::HostServer() {
	Host();
}