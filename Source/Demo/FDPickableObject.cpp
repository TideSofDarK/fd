// Fill out your copyright notice in the Description page of Project Settings.

#include "FDPickableObject.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FDInventoryComponent.h"

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

void AFDPickableObject::SetHidden(bool Hidden)
{
	Super::SetHidden(Hidden);

	ECollisionEnabled::Type collision = Hidden ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics;

	BoxComponent->SetCollisionEnabled(collision);
}

void AFDPickableObject::Interact(AActor* OtherActor)
{
	Super::Interact(OtherActor);

	UFDInventoryComponent* Inventory = OtherActor->FindComponentByClass<UFDInventoryComponent>();

	if (Inventory) {
		Inventory->AddItem(this);
		SetHidden(true);
	}
}
