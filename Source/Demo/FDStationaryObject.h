// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "FDGameplayObject.h"
#include "FDInteractableWithItem.h"
#include "FDStationaryObject.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AFDStationaryObject : public AFDGameplayObject, public IFDInteractableWithItem
{
	GENERATED_BODY()
	
public:
	/** AFDStationaryObject */
	AFDStationaryObject();

	/** Tick */
	virtual void Tick(float DeltaTime) override;

	/** InteractWithItem_Implementation */
	virtual void InteractWithItem_Implementation(AFDPickableObject *Item, AFDCharacter *OtherActor) override;

	/** CanInteractWith_Implementation */
	virtual bool CanInteractWith_Implementation(AFDPickableObject *Item) override;

  protected:
	/** BeginPlay */
	virtual void BeginPlay() override;

	/** FOnInteractWithItemDelegate */
	UPROPERTY(BlueprintAssignable, Category = "Gameplay Object")
	FOnInteractWithItemDelegate OnInteractWithItemDelegate;
};
