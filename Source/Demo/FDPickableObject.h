// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FDGameplayObject.h"
#include "FDPickableObject.generated.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** BoxComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;
};
