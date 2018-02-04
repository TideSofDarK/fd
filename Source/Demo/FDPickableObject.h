// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FDCharacter.h"
#include "FDGameplayObject.h"
#include "FDPickableObject.generated.h"

UENUM(BlueprintType)
enum class EObjectSize : uint8
{
	VE_Small 	UMETA(DisplayName = "Small"),
	VE_Large 	UMETA(DisplayName = "Large")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUsedDelegate, class AActor*, User);

/**
 * 
 */
UCLASS()
class DEMO_API AFDPickableObject : public AFDGameplayObject
{
	GENERATED_BODY()

private:
	/** Holder */
	AFDCharacter* Holder;

public:
	/** AFDPickableObject */
	AFDPickableObject();

	/** Interact_Implementation */
	virtual void Interact_Implementation(AActor* OtherActor) override;

	/** Use */
	UFUNCTION(BlueprintCallable, Category = "Pickable Object")
	virtual void Use(AActor* User);

	/** GetHolder */
	UFUNCTION(BlueprintPure, Category = "Pickable Object")
	AFDCharacter* GetHolder();

	/** SetHolder */
	UFUNCTION(BlueprintCallable, Category = "Pickable Object")
	void SetHolder(AFDCharacter* NewOwner);

	/** CanBeUsedOnItsOwn */
	UFUNCTION(BlueprintPure, Category = "Pickable Object")
	bool CanBeUsedOnItsOwn();

	/** GetAttachWhenActive */
	UFUNCTION(BlueprintPure, Category = "Pickable Object")
	bool GetAttachWhenActive();

	/** GetSocketName */
	UFUNCTION(BlueprintPure, Category = "Pickable Object")
	FName GetSocketName();

	/** GetCountText */
	UFUNCTION(BlueprintPure, Category = "Pickable Object")
	virtual FText GetCountText();

protected:
	/** BeginPlay */
	virtual void BeginPlay() override;

	/** ObjectSize */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickable Object")
	EObjectSize ObjectSize;

	/** bCanBeUsedOnItsOwn */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickable Object")
	bool bCanBeUsedOnItsOwn;

	/** DestroyAfterUse */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickable Object")
	bool bDestroyAfterUse;

	/** AttachWhenActive */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickable Object")
	bool bAttachWhenActive;

	/** SocketName */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickable Object")
	FName SocketName;

	/** OnUsedDelegate **/
	UPROPERTY(BlueprintAssignable, Category = "Pickable Object")
	FOnUsedDelegate OnUsedDelegate;
};
