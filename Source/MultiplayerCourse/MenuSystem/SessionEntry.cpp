// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionEntry.h"

void USessionEntry::Setup(uint32 EntryIndex) {
	CurrentEntryIndex = EntryIndex;
}

void USessionEntry::SetSessionName(const FString& Name) {
	SessionName->SetText(FText::FromString(Name));
	BtnEntry->OnClicked.AddDynamic(this, &USessionEntry::OnEntryClicked);
}

void USessionEntry::OnEntryClicked() {
	OnEntrySelected.Execute(CurrentEntryIndex);
}