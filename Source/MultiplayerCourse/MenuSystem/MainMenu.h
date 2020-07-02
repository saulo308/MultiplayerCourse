// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERCOURSE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetMenuInterface(IMenuInterface* InterfaceToSet) { MenuInterface = InterfaceToSet; }
	void Setup();
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

protected:
	virtual bool Initialize() override;
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
private:
	IMenuInterface* MenuInterface = nullptr;
};
