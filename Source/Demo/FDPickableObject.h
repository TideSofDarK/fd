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
	// Sets default values for this actor's properties
	AFDPickableObject();

	/** SetHidden **/
	UFUNCTION(BlueprintCallable, Category = "Gameplay Object")
	virtual void SetHidden(bool Hidden) override;

	/** Interact */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Object")
	virtual void Interact(AActor* OtherActor) override;

	/** Use */
	UFUNCTION(BlueprintCallable, Category = "Pickable Object")
	virtual void Use(AActor* User);

	/** GetHolder */
	UFUNCTION(BlueprintPure, Category = "Pickable Object")
	AFDCharacter* GetHolder();

	/** SetHolder */
	UFUNCTION(BlueprintCallable, Category = "Pickable Object")
	void SetHolder(AFDCharacter* NewOwner);

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

	/** DestroyAfterUse */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickable Object")
	bool DestroyAfterUse;

	/** AttachWhenActive */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickable Object")
	bool AttachWhenActive;

	/** SocketName */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickable Object")
	FName SocketName;

	/** OnUsedDelegate **/
	UPROPERTY(BlueprintAssignable, Category = "Pickable Object")
	FOnUsedDelegate OnUsedDelegate;
};
