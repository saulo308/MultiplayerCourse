// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERCOURSE_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	FORCEINLINE void AddTrigger() { ActiveTriggers++; }
	FORCEINLINE void RemoveTrigger() { if(ActiveTriggers > 0) ActiveTriggers--; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float MovingSpeed = 100.f;
	UPROPERTY(EditAnywhere, meta=(MakeEditWidget=true))
	FVector EndLocation;

private:
	FVector GlobalEndLocation;
	FVector GlobalStartLocation;

	UPROPERTY(EditAnywhere)
	int32 ActiveTriggers = 0;
};
