// Fill out your copyright notice in the Description page of Project Settings.

#include "FDGameplayObject.h"
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

	if (StaticMeshOverride) {
		StaticMeshComponent->SetStaticMesh(StaticMeshOverride);
	}
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
