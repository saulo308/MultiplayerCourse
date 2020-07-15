// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "SessionEntry.generated.h"

DECLARE_DELEGATE_OneParam(OnEntrySelectedDelegate, uint32)

/**
 * 
 */
UCLASS()
class MULTIPLAYERCOURSE_API USessionEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup(uint32 EntryIndex);
	void SetSessionName(const FString& Name);
	UFUNCTION()
	void OnEntryClicked();
	FORCEINLINE void SetIsSelected(bool Selected) { bIsSelected = Selected; }
	FORCEINLINE uint32 GetEntryIndex() { return CurrentEntryIndex;  }

public:
	OnEntrySelectedDelegate OnEntrySelected;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SessionName;
	UPROPERTY(meta = (BindWidget))
	UButton* BtnEntry;

	UPROPERTY(BlueprintReadOnly)
	bool bIsSelected = false;

private:
	uint32 CurrentEntryIndex;
};
