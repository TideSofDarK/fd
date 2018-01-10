// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "FDGameplayObject.h"
#include "FDStaticInteractableObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractWithItemDelegate, class AFDPickableObject*, Item);

/**
 * 
 */
UCLASS()
class DEMO_API AFDStaticInteractableObject : public AFDGameplayObject
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** InteractWithItem */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Object")
	virtual void InteractWithItem(AFDPickableObject* Item);

	/** CanInteractWith */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Object")
	virtual bool CanInteractWith(AFDPickableObject* Item);
	
protected:
	/** BeginPlay */
	virtual void BeginPlay() override;

	/** FOnInteractWithItemDelegate */
	UPROPERTY(BlueprintAssignable, Category = "Gameplay Object")
	FOnInteractWithItemDelegate OnInteractWithItemDelegate;
	
};
