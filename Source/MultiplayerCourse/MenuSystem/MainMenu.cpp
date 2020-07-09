// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Kismet/KismetSystemLibrary.h"

bool UMainMenu::Initialize() {
	if (!Super::Initialize()) return false;

	if (!BtnHost || !BtnJoinMenu || !BtnBackMenu || !BtnJoin || !BtnQuitGame) return false;
	BtnHost->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	BtnJoinMenu->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	BtnBackMenu->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	BtnJoin->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	BtnQuitGame->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true;
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld){
	RemoveWidget();
}

void UMainMenu::HostServer() {
	if (MenuInterface) {
		MenuInterface->HostServer();
	}
}

void UMainMenu::JoinServer() {
	if (MenuInterface) {
		
	}
}

void UMainMenu::OpenJoinMenu() {
	if (!MenuSwitcher || !JoinMenu) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
	RequestServerListRefresh();
}

void UMainMenu::OpenMainMenu() {
	if (!MenuSwitcher || !MainMenu) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::QuitGame() {
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(this, PlayerController,EQuitPreference::Quit,false);
}

void UMainMenu::RequestServerListRefresh() {
	if (!MenuInterface) return;
	//Requesting a refresh
	MenuInterface->RequestServerListRefresh();
}

void UMainMenu::SetServerList(TArray<FString>& ServerNames) {
	//Clearing all entris
	if (SessionList) SessionList->ClearChildren();

	//Creating Widgets
	for (auto ServerName : ServerNames) {
		AddSessionEntry(ServerName);
	}
}

void UMainMenu::AddSessionEntry(const FString& SessionName) {
	if (!SessionEntryClass || !SessionList) return;

	//Creating and setting up widget
	auto SessionWidget = CreateWidget<USessionEntry>(this, SessionEntryClass);
	SessionWidget->SetSessionName(SessionName);

	//Adding to scrollbox
	SessionList->AddChild(SessionWidget);
}
