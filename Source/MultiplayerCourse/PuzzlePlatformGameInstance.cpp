// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include "Engine/Engine.h"

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance() {
	UE_LOG(LogTemp, Warning, TEXT("Construct!"));
}

void UPuzzlePlatformGameInstance::Init() {
	UE_LOG(LogTemp, Warning, TEXT("Init!"));
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
	if (!Engine) return;

	Engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));
}