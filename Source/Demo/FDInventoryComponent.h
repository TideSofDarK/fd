// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Delegates/DelegateCombinations.h"
#include "FDPickableObject.h"
#include "FDInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddedItemToInventoryDelegate, class AFDGameplayObject*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemovedItemFromInventoryDelegate, class AFDGameplayObject*, Item);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMO_API UFDInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFDInventoryComponent();

	/** AddItem **/
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(AFDPickableObject* Item);

	/** EjectRandomItem **/
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	AFDPickableObject* EjectRandomItem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Items **/
	TArray<AFDPickableObject*> Items;

	/** OnAddedItemToInventoryDelegate **/
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnAddedItemToInventoryDelegate OnAddedItemToInventoryDelegate;

	/** FOnRemovedItemFromInventoryDelegate **/
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnRemovedItemFromInventoryDelegate OnRemovedItemFromInventoryDelegate;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
