// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "UObject/ConstructorHelpers.h"
#include "FDHexagonGrid2DCellComponent.h"
#include "FDHexagonGrid2D.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCellClickedDelegate, UFDHexagonGrid2DCellComponent*, HexagonGrid2DCellComponent);

UCLASS()
class DEMO_API AFDHexagonGrid2D : public AActor
{
	GENERATED_BODY()
	
public:	
	/** AFDHexagonGrid2D */
	AFDHexagonGrid2D();

	/** OnConstruction */
	virtual void OnConstruction(const FTransform & Transform) override;

	/** Tick */
	virtual void Tick(float DeltaTime) override;

#if WITH_EDITOR
	/** PostEditChangeProperty */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

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

	/** UpdateGrid */
	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid 2D")
	void UpdateGrid();

	/** IsValidCoords */
	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid 2D")
	bool IsValidCoords(FIntVector Coords);

	/** GetCell */
	UFUNCTION(BlueprintPure, Category = "Hexagon Grid 2D")
	UFDHexagonGrid2DCellComponent* GetCell(FIntVector Coords);

	/** GetAdjacentCellPaperSpriteComponents */
	UFUNCTION(BlueprintPure, Category = "Hexagon Grid 2D")
	TArray<UFDHexagonGrid2DCellComponent*> GetAdjacentCells(FIntVector Coords);

	/** GetCells */
	UFUNCTION(BlueprintPure, Category = "Hexagon Grid 2D")
	TArray<UFDHexagonGrid2DCellComponent*> GetCells();

	/** OnCellClickedDelegate */
	UPROPERTY(BlueprintAssignable, Category = "Hexagon Grid 2D")
	FOnCellClickedDelegate OnCellClickedDelegate;

private:
	/** CellClicked */
	UFUNCTION()
	void CellClicked(UPrimitiveComponent* PrimitiveComponent, FKey Key);

	/** SceneComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;

	/** CellsRootSceneComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* CellsRootSceneComponent;
};
