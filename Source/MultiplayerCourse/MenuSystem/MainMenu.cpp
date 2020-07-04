// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

bool UMainMenu::Initialize() {
	if (!Super::Initialize()) return false;

	if (!BtnHost || !BtnJoinMenu || !BtnBackMenu || !BtnJoin) return false;
	BtnHost->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	BtnJoinMenu->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	BtnBackMenu->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	BtnJoin->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
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
	auto IPAddress = IPAddressField->GetText();
	if (MenuInterface) {
		MenuInterface->JoinServer(IPAddress.ToString());
	}
}

void UMainMenu::OpenJoinMenu() {
	if (!MenuSwitcher || !JoinMenu) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu() {
	if (!MenuSwitcher || !MainMenu) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}
