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
	UFUNCTION(Exec)
	void Host();
	UFUNCTION(Exec)
	void Join(const FString& Address);
	UFUNCTION(Exec,BlueprintCallable)
	void LoadMenu();

	UFUNCTION()
	virtual void HostServer() override;
protected:
	UPROPERTY()
	TSubclassOf<UUserWidget> MenuClass;
};
