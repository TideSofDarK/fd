// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FDInteractableWithItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractWithItemDelegate, class AFDPickableObject *, Item, class AFDCharacter *, OtherActor);

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UFDInteractableWithItem : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEMO_API IFDInteractableWithItem
{
	GENERATED_BODY()

public:
	/** CanInteractWith */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	bool CanInteractWith(AFDPickableObject *Item);

	/** InteractWithItem */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void InteractWithItem(AFDPickableObject *Item, AFDCharacter *OtherActor);
};
