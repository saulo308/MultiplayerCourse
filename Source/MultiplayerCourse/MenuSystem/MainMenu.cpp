// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Kismet/KismetSystemLibrary.h"

bool UMainMenu::Initialize() {
	if (!Super::Initialize()) return false;

	if (!BtnHost || !BtnJoinMenu || !BtnBackMenu || !BtnJoin || !BtnQuitGame) return false;
	BtnHost->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	BtnHostMenu->OnClicked.AddDynamic(this, &UMainMenu::OpenHostMenu);
	BtnJoinMenu->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	BtnBackMenu->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	BtnCancel->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	BtnJoin->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	BtnQuitGame->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true;
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld){
	RemoveWidget();
}

void UMainMenu::HostServer() {
	if (MenuInterface) {
		MenuInterface->HostServer(SessionNameText->GetText().ToString());
	}
}

void UMainMenu::JoinServer() {
	if (!MenuInterface) return;

	//Joining server on SelectedEntryIndex
	if (SelectedEntryIndex.IsSet()) {
		UE_LOG(LogTemp, Warning, TEXT("Server selected: %d"), SelectedEntryIndex.GetValue());
		MenuInterface->JoinServer(SelectedEntryIndex.GetValue());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Server index not yet selected!"));
	}
}

void UMainMenu::OpenJoinMenu() {
	if (!MenuSwitcher || !JoinMenu) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
	RequestServerListRefresh();
}

void UMainMenu::OpenHostMenu() {
	if (!MenuSwitcher || !JoinMenu) return;
	MenuSwitcher->SetActiveWidget(HostMenu);
}

void UMainMenu::OpenMainMenu() {
	if (!MenuSwitcher || !MainMenu) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::QuitGame() {
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(this, PlayerController,EQuitPreference::Quit,false);
}

void UMainMenu::RequestServerListRefresh() {
	if (!MenuInterface) return;
	//Requesting a refresh
	MenuInterface->RequestServerListRefresh();
}

void UMainMenu::SetServerList(TArray<FServerData>& InServersData) {
	//Clearing all entris
	if (SessionList) SessionList->ClearChildren();

	//Creating Widgets
	uint32 i = 0;
	for (auto ServerData : InServersData) {
		AddSessionEntry(ServerData,i);
		++i;
	}
}

void UMainMenu::AddSessionEntry(const FServerData& ServerData,uint32 EntryIndex) {
	if (!SessionEntryClass || !SessionList) return;

	//Creating and setting up widget
	auto SessionWidget = CreateWidget<USessionEntry>(this, SessionEntryClass);

	//Setting info
	SessionWidget->SetSessionName(ServerData.ServerName);
	SessionWidget->SetHostName(ServerData.HostName);
	SessionWidget->SetSlots(ServerData.CurConnectedPlayerNum,ServerData.MaxConnectedPlayerNum);

	//Setup
	SessionWidget->Setup(EntryIndex);
	SessionWidget->OnEntrySelected.BindUObject(this, &UMainMenu::SetSelectedEntryIndex);

	//Adding to scrollbox
	SessionList->AddChild(SessionWidget);
}

void UMainMenu::SetSelectedEntryIndex(uint32 NewIndex){ 
	SelectedEntryIndex = NewIndex;
	UpdateEntries(NewIndex);
}

void UMainMenu::UpdateEntries(uint32 NewIndex) {
	auto Children = SessionList->GetAllChildren();
	for (auto Child : Children) {
		USessionEntry* Entry = Cast<USessionEntry>(Child);
		if (!Entry) continue;

		if (Entry->GetEntryIndex() == NewIndex) {
			Entry->SetIsSelected(true);
		}else {
			Entry->SetIsSelected(false);
		}
	}
}