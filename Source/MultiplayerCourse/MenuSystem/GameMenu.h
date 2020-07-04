// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "Components/Button.h"
#include "GameMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERCOURSE_API UGameMenu : public UMenuBase
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
	UFUNCTION()
	void QuitPressed();

public:
	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;
	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;
};
