#include "FDStaticInteractableObject.h"

void AFDStaticInteractableObject::BeginPlay()
{
	Super::BeginPlay();

}

void AFDStaticInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFDStaticInteractableObject::InteractWithItem(AFDPickableObject* Item, AFDCharacter* OtherActor)
{
	OnInteractWithItemDelegate.Broadcast(Item, OtherActor);
}

//bool AFDStaticInteractableObject::CanInteractWith(AFDPickableObject* Item)
//{
//	return false;
//}