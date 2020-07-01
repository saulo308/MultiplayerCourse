// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

bool UMainMenu::Initialize() {
	if (!Super::Initialize()) return false;

	if (!BtnHost || !BtnJoin) return false;
	BtnHost->OnClicked.AddDynamic(this, &UMainMenu::OnHostClicked);
	BtnJoin->OnClicked.AddDynamic(this, &UMainMenu::OnJoinClicked);
	return true;
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