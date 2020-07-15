// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionEntry.h"

void USessionEntry::Setup(uint32 EntryIndex) {
	CurrentEntryIndex = EntryIndex;
}

void USessionEntry::SetSessionName(const FString& Name) {
	SessionName->SetText(FText::FromString(Name));
	BtnEntry->OnClicked.AddDynamic(this, &USessionEntry::OnEntryClicked);
}

void USessionEntry::SetHostName(const FString& Name) {
	HostName->SetText(FText::FromString(Name));
}

void USessionEntry::SetSlots(uint16 CurrentNum, uint16 MaxNum) {
	FText SlotString = FText::FromString(FString::Printf(TEXT("%d/%d"), CurrentNum, MaxNum));
	Slots->SetText(SlotString);
}

void USessionEntry::OnEntryClicked() {
	OnEntrySelected.Execute(CurrentEntryIndex);
}
