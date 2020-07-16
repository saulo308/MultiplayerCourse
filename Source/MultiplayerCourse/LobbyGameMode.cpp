// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer) {
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("Welcome new player!"));
	++ConnectedPlayerNum;

	if (ConnectedPlayerNum >= 2) {
		UE_LOG(LogTemp, Warning, TEXT("Has reached top player num!!!!"));

		//Seamless travel
		bUseSeamlessTravel = true;

		//Travelling
		auto World = GetWorld();
		if (!World) return;
		World->ServerTravel(TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen"));
	}
}

void ALobbyGameMode::Logout(AController* Exiting) {
	Super::Logout(Exiting);
	UE_LOG(LogTemp, Warning, TEXT("Bye bye!"));
	--ConnectedPlayerNum;
}