// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "FDPickableObject.h"
#include "FDFirearm.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFired, FHitResult, HitResult);

/**
 * 
 */
UCLASS()
class DEMO_API AFDFirearm : public AFDPickableObject
{
	GENERATED_BODY()

public:
	/** Use */
	UFUNCTION(BlueprintCallable, Category = Firearm)
	virtual void Use(AActor* User) override;
	
protected:
	AFDFirearm();

	/** MagazineCapacity */
	UPROPERTY(EditDefaultsOnly, Category = Firearm)
	int MagazineCapacity;

	/** Damage */
	UPROPERTY(EditDefaultsOnly, Category = Firearm)
	int Damage;

	/** AudioComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* AudioComponent;
	
	/** Fire */
	UFUNCTION(BlueprintCallable, Category = Firearm)
	void Fire();

	/** GetCountText */
	UFUNCTION(BlueprintPure, Category = "Pickable Object")
	virtual FText GetCountText() override;

	/** OnFired */
	UPROPERTY(BlueprintAssignable, Category = Firearm)
	FOnFired OnFired;
};