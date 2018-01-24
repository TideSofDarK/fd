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
	// Hide previously attached item
	if (Items.IsValidIndex(ActiveInventoryItemIndex) && Items[ActiveInventoryItemIndex]->GetAttachWhenActive())
	{
		Items[ActiveInventoryItemIndex]->SetGameplayObjectState(EGameplayObjectState::VE_DisabledHidden);
	}

	if (Items.Num() < ActiveInventoryItemIndex - 1)
	{
		ActiveInventoryItemIndex = -1;
	}

	if (ActiveInventoryItemIndex == -1)
	{
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

	// Attach and show if need
	if (Items[ActiveInventoryItemIndex]->GetAttachWhenActive())
	{
		Items[ActiveInventoryItemIndex]->SetGameplayObjectState(EGameplayObjectState::VE_DisabledVisible);
		Items[ActiveInventoryItemIndex]->AttachToComponent(GetOwner()->FindComponentByClass<USceneComponent>(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Items[ActiveInventoryItemIndex]->GetSocketName());
	}

	OnLoopInvetoryDelegate.Broadcast(ActiveInventoryItemIndex);

	return ActiveInventoryItemIndex;
}

void UFDInventoryComponent::AddItem(AFDPickableObject * Item)
{
	int Index = Items.AddUnique(Item);
	OnAddedItemToInventoryDelegate.Broadcast(Item);

	if (ActiveInventoryItemIndex == -1)
	{
		LoopInventory();
	}
}

void UFDInventoryComponent::RemoveItem(AFDPickableObject * Item)
{
	Items.Remove(Item);
	OnRemovedItemFromInventoryDelegate.Broadcast(Item);

	if (!Items.Num())
	{
		ActiveInventoryItemIndex = -1;
	}
	else
	{
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

