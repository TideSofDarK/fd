// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "FDHexagonGrid2DCellComponent.generated.h"

UENUM(BlueprintType)
enum class ECellType : uint8
{
	VE_Regular 	UMETA(DisplayName = "Regular"),
	VE_Target 	UMETA(DisplayName = "Target"),
	VE_Wall	UMETA(DisplayName = "Wall")
};

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DEMO_API UFDHexagonGrid2DCellComponent : public UPaperSpriteComponent
{
	GENERATED_BODY()
	
public:
	/** GetCoords */
	UFUNCTION(BlueprintPure, Category = "Hexagon Grid 2D Cell")
	FORCEINLINE FIntVector GetCoords() const { return Coords; }

	/** GetCellColor */
	UFUNCTION(BlueprintPure, Category = "Hexagon Grid 2D Cell")
	int GetCellColor() { return CellColor; }

	/** SetCoords */
	UFUNCTION(BlueprintInternalUseOnly, Category = "Hexagon Grid 2D Cell")
	void SetCoords(FIntVector NewCoords) { Coords = NewCoords; }

	/** SetCellColor */
	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid 2D Cell")
	void SetCellColor(int NewCellColor);

	/** IncrementCellColor */
	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid 2D Cell")
	void IncrementCellColor();

protected:
	/** Coords */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon Grid 2D Cell")
	FIntVector Coords;
	
	/** CellType */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon Grid 2D Cell")
	ECellType CellType;

	/** CellColor */
	UPROPERTY()
	int CellColor;
};
