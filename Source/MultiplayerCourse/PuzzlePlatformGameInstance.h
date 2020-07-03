// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERCOURSE_API UPuzzlePlatformGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformGameInstance();

	//Exec functions
	UFUNCTION(Exec,BlueprintCallable)
	void LoadMenu();

	UFUNCTION(Exec)
	virtual void HostServer() override;
	UFUNCTION(Exec)
	virtual void JoinServer(const FString& Address) override;
protected:
	UPROPERTY()
	TSubclassOf<UUserWidget> MenuClass;
};
