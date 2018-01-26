// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "UObject/ConstructorHelpers.h"
#include "FDHexagonGrid2DCellComponent.h"
#include "FDHexagonGrid2D.generated.h"

USTRUCT()
struct FCellsArray
{
	GENERATED_BODY()

	TArray<UFDHexagonGrid2DCellComponent*> Cells;

public:

	/** IsValidIndex */
	bool IsValidIndex(uint32 Index)
	{
		return Cells.IsValidIndex(Index);
	}

	/** operator[] */
	UFDHexagonGrid2DCellComponent* operator[] (int32 i)
	{
		return Cells[i];
	}

	/** Ad */
	void Add(UFDHexagonGrid2DCellComponent* Cell)
	{
		Cells.Add(Cell);
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCellClickedDelegate, UFDHexagonGrid2DCellComponent*, HexagonGrid2DCellComponent);

UCLASS()
class DEMO_API AFDHexagonGrid2D : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFDHexagonGrid2D();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** GridWidth */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Hexagon Grid 2D")
	int GridWidth;

	/** GridHeight */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Hexagon Grid 2D")
	int GridHeight;

	/** CellSprite */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Hexagon Grid 2D")
	UPaperSprite * CellSprite;

	/** IsValidCoords */
	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid 2D")
	bool IsValidCoords(FIntVector Coords);

	/** GetCell */
	UFUNCTION(BlueprintPure, Category = "Hexagon Grid 2D")
	UFDHexagonGrid2DCellComponent* GetCell(FIntVector Coords);

	/** GetAdjacentCellPaperSpriteComponents */
	UFUNCTION(BlueprintPure, Category = "Hexagon Grid 2D")
	TArray<UFDHexagonGrid2DCellComponent*> GetAdjacentCells(FIntVector Coords);

	/** OnCellClickedDelegate */
	UPROPERTY(BlueprintAssignable, Category = "Hexagon Grid 2D")
	FOnCellClickedDelegate OnCellClickedDelegate;

private:
	/** Cells */
	TArray<FCellsArray> Cells;

	/** CellClicked */
	UFUNCTION()
	void CellClicked(UPrimitiveComponent* PrimitiveComponent, FKey Key);

	/** SceneComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;
};
