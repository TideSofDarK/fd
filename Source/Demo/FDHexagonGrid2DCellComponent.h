// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "UObject/ConstructorHelpers.h"
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
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), HideCategories = (Sprite))
class DEMO_API UFDHexagonGrid2DCellComponent : public UPaperSpriteComponent
{
	GENERATED_BODY()
	
public:
	/** UFDHexagonGrid2DCellComponent */
	UFDHexagonGrid2DCellComponent();

#if WITH_EDITOR
	/** PostEditChangeProperty */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	/** GetCoords */
	UFUNCTION(BlueprintPure, Category = "Hexagon Grid 2D Cell")
	FORCEINLINE FIntVector GetCoords() const { return Coords; }

	/** GetCellType */
	UFUNCTION(BlueprintPure, Category = "Hexagon Grid 2D Cell")
	FORCEINLINE ECellType GetCellType() const { return CellType; };

	/** GetCellColor */
	UFUNCTION(BlueprintPure, Category = "Hexagon Grid 2D Cell")
	int GetCellColor() { return CellColor; }

	/** SetCoords */
	UFUNCTION(BlueprintInternalUseOnly, Category = "Hexagon Grid 2D Cell")
	void SetCoords(FIntVector NewCoords) { Coords = NewCoords; }

	/** SetCellType */
	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid 2D Cell")
	void SetCellType(ECellType NewCellType);

	/** SetCellColor */
	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid 2D Cell")
	void SetCellColor(int NewCellColor);

	/** IncrementCellColor */
	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid 2D Cell")
	void IncrementCellColor();

protected:
	/** CellSprite */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Hexagon Grid 2D")
	UPaperSprite * CellSprite;

	/** WallCellSprite */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Hexagon Grid 2D")	
	UPaperSprite * WallCellSprite;
	
	/** TargetCellSprite */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Hexagon Grid 2D")
	UPaperSprite * TargetCellSprite;

	/** Coords */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hexagon Grid 2D Cell")
	FIntVector Coords;
	
	/** CellType */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hexagon Grid 2D Cell")
	ECellType CellType;

	/** CellColor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon Grid 2D Cell")
	int CellColor;
};
