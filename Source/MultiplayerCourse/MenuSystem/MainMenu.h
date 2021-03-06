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

USTRUCT()
struct FServerData {
	GENERATED_BODY()

public:
	FString ServerName;
	FString HostName;
	uint16 CurConnectedPlayerNum;
	uint16 MaxConnectedPlayerNum;
};

/**
 * 
 */
UCLASS()
class MULTIPLAYERCOURSE_API UMainMenu : public UMenuBase
{
	GENERATED_BODY()

public:
	void SetServerList(TArray<FServerData>& InServersData);
	void SetSelectedEntryIndex(uint32 NewIndex);
	void UpdateEntries(uint32 NewIndex);

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
	void OpenHostMenu();
	UFUNCTION()
	void QuitGame();
	void RequestServerListRefresh();
	void AddSessionEntry(const FServerData& ServerData, uint32 EntryIndex);

public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* BtnHost;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BtnHostMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BtnJoinMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BtnJoin;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BtnBackMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BtnQuitGame;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BtnCancel;

	//Menus
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* MainMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* JoinMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* HostMenu;

	//Menus
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* SessionNameText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* SessionList;

	//SessionEntry
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<USessionEntry> SessionEntryClass;
protected:
	TOptional<uint32> SelectedEntryIndex;
};
