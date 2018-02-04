// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FDInteractable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractDelegate, class AActor*, OtherActor);

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UFDInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEMO_API IFDInteractable
{
	GENERATED_BODY()

public:
	/** Interact */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void Interact(AActor* OtherActor);
};
