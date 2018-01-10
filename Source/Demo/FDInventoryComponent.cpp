// Fill out your copyright notice in the Description page of Project Settings.

#include "FDInventoryComponent.h"


// Sets default values for this component's properties
UFDInventoryComponent::UFDInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ActiveInventoryItemIndex = -1;
}

int UFDInventoryComponent::LoopInventory()
{
	if (ActiveInventoryItemIndex == -1) {
		if (Items.Num() > 0)
		{
			ActiveInventoryItemIndex = 0;
		}
		else
		{
			return ActiveInventoryItemIndex;
		}
	}

	ActiveInventoryItemIndex++;

	if (ActiveInventoryItemIndex >= Items.Num())
	{
		ActiveInventoryItemIndex = 0;
	}

	OnLoopInvetoryDelegate.Broadcast(ActiveInventoryItemIndex);
	
	UE_LOG(LogTemp, Warning, TEXT("Num is %d"), Items.Num());
	UE_LOG(LogTemp, Warning, TEXT("Index is %d"), ActiveInventoryItemIndex);

	return ActiveInventoryItemIndex;
}

void UFDInventoryComponent::AddItem(AFDPickableObject * Item)
{
	int Index = Items.AddUnique(Item);
	OnAddedItemToInventoryDelegate.Broadcast(Item);

	if (ActiveInventoryItemIndex == -1) {
		LoopInventory();
	}
}

AFDPickableObject* UFDInventoryComponent::EjectRandomItem()
{
	if (Items.Num() > 0)
	{
		AFDPickableObject* EjectedItem = Items.Last();
		Items.Remove(EjectedItem);
		OnRemovedItemFromInventoryDelegate.Broadcast(EjectedItem);

		return EjectedItem;
	}
	else
	{
		return nullptr;
	}
}

AFDPickableObject* UFDInventoryComponent::GetItemByIndex(int Index)
{
	return Items[Index];
}

AFDPickableObject* UFDInventoryComponent::GetActiveItem()
{
	if (ActiveInventoryItemIndex == -1)
	{
		return nullptr;
	}

	return Items[ActiveInventoryItemIndex];
}

// Called when the game starts
void UFDInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UFDInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

