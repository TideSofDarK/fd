// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "FDHexagonGrid2DCellComponent.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UFDHexagonGrid2DCellComponent : public UPaperSpriteComponent
{
	GENERATED_BODY()
	
public:
	/** GetCoords */
	UFUNCTION(BlueprintPure, Category = "Hexagon Grid 2D Cell")
	FORCEINLINE FIntVector GetCoords() const { return Coords; }

	/** SetCoords */
	UFUNCTION(BlueprintInternalUseOnly, Category = "Hexagon Grid 2D Cell")
	void SetCoords(FIntVector NewCoords) { Coords = NewCoords; }

protected:
	/** Coords */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon Grid 2D Cell")
	FIntVector Coords;
	
};
