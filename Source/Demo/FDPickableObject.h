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

protected:
	/** BeginPlay */
	virtual void BeginPlay() override;

	/** BoxComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	/** ObjectSize */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Object")
	EObjectSize ObjectSize;
};
