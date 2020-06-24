// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "MovingPlatform.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root
	Root = CreateAbstractDefaultSubobject<USceneComponent>(FName("Root"));
	RootComponent = Root;
	//StaticMesh
	TriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("TriggerMesh"));
	if (TriggerMesh) {
		TriggerMesh->SetupAttachment(Root);
	}
	//TriggerVolume
	TriggerVolume = CreateAbstractDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (TriggerVolume) {
		TriggerVolume->SetupAttachment(Root);
	}
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

	//Overlaps
	if (TriggerVolume) {
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnTriggerBeginOverlap);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnTriggerEndOverlap);
	}
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlatformTrigger::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	for(auto Platform : PlatformTriggers)
		Platform->AddTrigger();
}

void APlatformTrigger::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	for (auto Platform : PlatformTriggers)
		Platform->RemoveTrigger();
}

