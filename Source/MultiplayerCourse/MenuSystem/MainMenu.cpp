// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

bool UMainMenu::Initialize() {
	if (!Super::Initialize()) return false;

	if (!BtnHost || !BtnJoin) return false;
	BtnHost->OnClicked.AddDynamic(this, &UMainMenu::OnHostClicked);
	BtnJoin->OnClicked.AddDynamic(this, &UMainMenu::OnJoinClicked);
	return true;
}

void UMainMenu::Setup() {
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	//Adding to viewport
	AddToViewport();
	bIsFocusable = true;

	//InputMode
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld){
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	//InputMode
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(FInputModeGameOnly());

	//Removing from viewport
	RemoveFromParent();
	bIsFocusable = false;
}

void UMainMenu::OnHostClicked() {
	UE_LOG(LogTemp, Warning, TEXT("Host!"));
	if (MenuInterface) {
		MenuInterface->HostServer();
	}
}

void UMainMenu::OnJoinClicked() {
	UE_LOG(LogTemp, Warning, TEXT("Join!"));
}