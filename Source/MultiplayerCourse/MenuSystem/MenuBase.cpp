// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuBase.h"


void UMenuBase::Setup() {
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

void UMenuBase::RemoveWidget() {
	//Removing from parent
	RemoveFromParent();
	bIsFocusable = false;

	//Setting InputMode
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;
	PlayerController->SetInputMode(FInputModeGameOnly());
}