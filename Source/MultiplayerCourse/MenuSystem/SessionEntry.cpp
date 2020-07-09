// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionEntry.h"

void USessionEntry::SetSessionName(const FString& Name) {
	SessionName->SetText(FText::FromString(Name));
}