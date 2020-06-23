// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay() {
	Super::BeginPlay();

	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalEndLocation = GetTransform().TransformPosition(EndLocation);
}

void AMovingPlatform::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (HasAuthority()) {
		//Moving platform
		auto CurrentLocation = GetActorLocation();
		auto MovementDirection = (GlobalEndLocation - GlobalStartLocation).GetSafeNormal();
		CurrentLocation += MovementDirection * MovingSpeed * DeltaTime;
		SetActorLocation(CurrentLocation);

		//If has reached the end location, swap with start and platform will back to "StartLocation"s
		if (CurrentLocation.Equals(GlobalEndLocation,0.1f)) {
			auto TempLocation = GlobalStartLocation;
			GlobalStartLocation = GlobalEndLocation;
			GlobalEndLocation = TempLocation;
		}
	}
}