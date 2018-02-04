#include "FDStationaryObject.h"

AFDStationaryObject::AFDStationaryObject()
{
	InputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("ObjectInputComponent"));
	InputComponent->bBlockInput = bBlockInput;
}

void AFDStationaryObject::BeginPlay()
{
	Super::BeginPlay();

}

void AFDStationaryObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFDStationaryObject::InteractWithItem_Implementation(AFDPickableObject* Item, AFDCharacter* OtherActor)
{
	OnInteractWithItemDelegate.Broadcast(Item, OtherActor);
}

bool AFDStationaryObject::CanInteractWith_Implementation(AFDPickableObject* Item)
{
	return false;
}