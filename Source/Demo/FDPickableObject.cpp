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

	bCanBeUsedOnItsOwn = false;
}

void AFDPickableObject::BeginPlay()
{
	Super::BeginPlay();

}

void AFDPickableObject::Interact(AActor* OtherActor)
{
	Super::Interact(OtherActor);

	UFDInventoryComponent* Inventory = OtherActor->FindComponentByClass<UFDInventoryComponent>();

	if (Inventory)
	{
		bBypassNearestObjectDetection = true;
		SetGameplayObjectState(EGameplayObjectState::VE_DisabledHidden);

		if (OtherActor->IsA<AFDCharacter>())
		{
			SetHolder(Cast<AFDCharacter>(OtherActor));
		}

		Inventory->AddItem(this);
	}
}

void AFDPickableObject::Use(AActor* User)
{
	OnUsedDelegate.Broadcast(User);

	UFDInventoryComponent* Inventory = User->FindComponentByClass<UFDInventoryComponent>();

	if (Inventory)
	{
		if (bDestroyAfterUse)
		{
			Inventory->RemoveItem(this);
			Destroy();
		}
	}
}

AFDCharacter* AFDPickableObject::GetHolder()
{
	return Holder;
}

void AFDPickableObject::SetHolder(AFDCharacter* NewHolder)
{
	Holder = NewHolder;
}

bool AFDPickableObject::CanBeUsedOnItsOwn()
{
	return bCanBeUsedOnItsOwn;
}

bool AFDPickableObject::GetAttachWhenActive()
{
	return bAttachWhenActive;
}

FName AFDPickableObject::GetSocketName()
{
	return SocketName;
}

FText AFDPickableObject::GetCountText()
{
	return FText::FromString("");
}