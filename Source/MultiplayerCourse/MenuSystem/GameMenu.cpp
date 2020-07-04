// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenu.h"

bool UGameMenu::Initialize() {
	if (!Super::Initialize()) return false;
	if (!CancelButton || !MainMenuButton) return false;

	CancelButton->OnClicked.AddDynamic(this, &UMenuBase::RemoveWidget);
	MainMenuButton->OnClicked.AddDynamic(this, &UGameMenu::QuitPressed);

	return true;
}

void UGameMenu::QuitPressed() {
	RemoveWidget();

	if (!MenuInterface) return;
	MenuInterface->BackToMainMenu();
}