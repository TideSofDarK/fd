// Fill out your copyright notice in the Description page of Project Settings.

#include "FDPickableObject.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFDPickableObject::AFDPickableObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
}

void AFDPickableObject::BeginPlay()
{
	Super::BeginPlay();

}

