// Fill out your copyright notice in the Description page of Project Settings.

#include "FDStaticInteractableObject.h"

// Called when the game starts or when spawned
void AFDStaticInteractableObject::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFDStaticInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFDStaticInteractableObject::InteractWithItem(AFDPickableObject* Item)
{
	OnInteractWithItemDelegate.Broadcast(Item);
}

bool AFDStaticInteractableObject::CanInteractWith(AFDPickableObject* Item)
{
	return false;
}