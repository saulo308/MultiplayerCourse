// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MenuBase.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERCOURSE_API UMenuBase : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetMenuInterface(IMenuInterface* InterfaceToSet) { MenuInterface = InterfaceToSet; }
	void Setup();
	UFUNCTION()
	void RemoveWidget();

protected:
	IMenuInterface* MenuInterface = nullptr;
};
