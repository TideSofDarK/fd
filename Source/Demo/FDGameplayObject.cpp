// Fill out your copyright notice in the Description page of Project Settings.

#include "FDGameplayObject.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFDGameplayObject::AFDGameplayObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);

	bBypassNearestObjectDetection = false;
	GameplayObjectState = EGameplayObjectState::VE_EnabledVisible;
}

void AFDGameplayObject::SetGameplayObjectState(EGameplayObjectState NewGameplayObjectState)
{
	bool bEnabled = NewGameplayObjectState == EGameplayObjectState::VE_EnabledVisible ||
					NewGameplayObjectState == EGameplayObjectState::VE_EnabledHidden;

	bool bVisible = NewGameplayObjectState == EGameplayObjectState::VE_EnabledVisible ||
					NewGameplayObjectState == EGameplayObjectState::VE_DisabledVisible;

	SetActorTickEnabled(bEnabled);
	SetActorEnableCollision(bEnabled);
	SetActorHiddenInGame(!bVisible);
}

// Called when the game starts or when spawned
void AFDGameplayObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFDGameplayObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFDGameplayObject::Interact(AActor* OtherActor)
{
	OnInteractDelegate.Broadcast(OtherActor);
}

bool AFDGameplayObject::GetBypassNearestObjectDetection()
{
	return bBypassNearestObjectDetection;
}