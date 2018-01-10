// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FDGameplayObject.h"
#include "FDPickableObject.generated.h"

UENUM(BlueprintType)
enum class EObjectSize : uint8
{
	VE_Small 	UMETA(DisplayName = "Small"),
	VE_Large 	UMETA(DisplayName = "Large")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUsedDelegate);

/**
 * 
 */
UCLASS()
class DEMO_API AFDPickableObject : public AFDGameplayObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFDPickableObject();

	/** GetBoxComponent **/
	FORCEINLINE class UBoxComponent* GetBoxComponent() { return BoxComponent; }

	/** SetHidden **/
	UFUNCTION(BlueprintCallable, Category = "Gameplay Object")
	virtual void SetHidden(bool Hidden) override;

	/** Interact */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Object")
	virtual void Interact(AActor* OtherActor) override;

	/** Use */
	UFUNCTION(BlueprintCallable, Category = "Pickable Object")
	virtual void Use();

protected:
	/** BeginPlay */
	virtual void BeginPlay() override;

	/** BoxComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	/** ObjectSize */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickable Object")
	EObjectSize ObjectSize;

	/** OnUsedDelegate **/
	UPROPERTY(BlueprintAssignable, Category = "Pickable Object")
	FOnUsedDelegate OnUsedDelegate;
};
