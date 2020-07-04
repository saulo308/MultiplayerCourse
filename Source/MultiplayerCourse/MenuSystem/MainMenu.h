// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERCOURSE_API UMainMenu : public UMenuBase
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	UFUNCTION()
	void HostServer();
	UFUNCTION()
	void JoinServer();
	UFUNCTION()
	void OpenJoinMenu();
	UFUNCTION()
	void OpenMainMenu();

public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* BtnHost;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BtnJoinMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BtnJoin;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BtnBackMenu;

	//Menus
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* MainMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* JoinMenu;

	//IPField
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* IPAddressField;
};
