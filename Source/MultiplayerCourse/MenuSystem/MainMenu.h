// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERCOURSE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;
	UFUNCTION()
	void OnHostClicked();
	UFUNCTION()
	void OnJoinClicked();

public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* BtnHost;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BtnJoin;
};
