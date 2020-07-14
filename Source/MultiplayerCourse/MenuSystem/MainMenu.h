// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "SessionEntry.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERCOURSE_API UMainMenu : public UMenuBase
{
	GENERATED_BODY()

public:
	void SetServerList(TArray<FString>& ServerNames);
	FORCEINLINE void SetSelectedEntryIndex(uint32 NewIndex) { SelectedEntryIndex = NewIndex; }

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
	UFUNCTION()
	void QuitGame();
	void RequestServerListRefresh();
	void AddSessionEntry(const FString& SessionName, uint32 EntryIndex);

public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* BtnHost;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BtnJoinMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BtnJoin;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BtnBackMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BtnQuitGame;

	//Menus
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* MainMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* JoinMenu;

	//IPField
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* SessionList;

	//SessionEntry
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<USessionEntry> SessionEntryClass;
protected:
	TOptional<uint32> SelectedEntryIndex;
};
