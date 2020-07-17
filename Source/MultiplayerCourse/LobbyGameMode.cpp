// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "PuzzlePlatformGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer) {
	Super::PostLogin(NewPlayer);
	++ConnectedPlayerNum;

	if (ConnectedPlayerNum >= 2) {
		UE_LOG(LogTemp, Warning, TEXT("Game will start in 10 seconds!!!!"));
		auto World = GetWorld();
		if (!World) return;

		FTimerHandle TimerHandle;
		World->GetTimerManager().SetTimer(TimerHandle,this,&ALobbyGameMode::StartSession,10.f,false);
	}
}

void ALobbyGameMode::StartSession() {
	auto GameInstance = Cast<UPuzzlePlatformGameInstance>(GetGameInstance());
	if (!GameInstance) return;

	//Seamless travel flag
	bUseSeamlessTravel = true;
	//Starting Session
	GameInstance->StartSession();
}

void ALobbyGameMode::Logout(AController* Exiting) {
	Super::Logout(Exiting);
	--ConnectedPlayerNum;
}