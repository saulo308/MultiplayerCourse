// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerCourseGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERCOURSE_API ALobbyGameMode : public AMultiplayerCourseGameMode
{
	GENERATED_BODY()

public:
	FORCEINLINE uint16 GetConnectedPlayerNum() { return ConnectedPlayerNum; }

	virtual void PostLogin(APlayerController* NewPlayer) override;
	void StartSession();
	virtual void Logout(AController* Exiting) override;
	
private:
	uint16 ConnectedPlayerNum = 0;
};
