// Fill out your copyright notice in the Description page of Project Settings.

#include "FDHexagonGrid2D.h"

// Sets default values
AFDHexagonGrid2D::AFDHexagonGrid2D()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
}

// Called when the game starts or when spawned
void AFDHexagonGrid2D::BeginPlay()
{
	Super::BeginPlay();

	if (!CellSprite->IsValidLowLevel())
	{
		return;
	}

	FVector2D SourceSize = CellSprite->GetSourceSize();

	for (auto X = 0; X < GridWidth; X++)
	{
		Cells.Add(FCellsArray());
		for (auto Y = 0; Y < GridHeight; ++Y)
		{
			float HalfWidth = SourceSize.X / 2;
			float YOffset = (sqrt(3) / 2 * SourceSize.X) * Y;
			if (X % 2 != 0)
			{
				YOffset += (sqrt(3) / 2 * HalfWidth);
			}

			UFDHexagonGrid2DCellComponent* Cell = NewObject<UFDHexagonGrid2DCellComponent>(this, *FString("CellSpriteComponent" + FString::FromInt(X) + FString::FromInt(Y)));
			Cell->RegisterComponent();
			Cell->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
			Cell->SetupAttachment(RootComponent);
			Cell->SetSprite(CellSprite);
			Cell->OnClicked.AddDynamic(this, &AFDHexagonGrid2D::CellClicked);
			Cell->SetRelativeLocation(FVector4(HalfWidth * 3 / 2 * X, 0, YOffset));
			Cell->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
			Cell->SetCoords(FIntVector(X, Y, 0));
			EnableInput(GetWorld()->GetFirstPlayerController());

			Cells[X].Add(Cell);
		}
	}
}

// Called every frame
void AFDHexagonGrid2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFDHexagonGrid2D::CellClicked(UPrimitiveComponent* PrimitiveComponent, FKey Key)
{
	UFDHexagonGrid2DCellComponent* Cell = Cast<UFDHexagonGrid2DCellComponent>(PrimitiveComponent);
	if (Cell->IsValidLowLevelFast())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, Cell->GetCoords().ToString());
	
		OnCellClickedDelegate.Broadcast(Cell);
	}
}

bool AFDHexagonGrid2D::IsValidCoords(FIntVector Coords)
{
	return (Cells.IsValidIndex(Coords.X) && Cells[Coords.X].IsValidIndex(Coords.Y));
}

UFDHexagonGrid2DCellComponent* AFDHexagonGrid2D::GetCell(FIntVector Coords)
{
	return Cells[Coords.X][Coords.Y];
}

TArray<UFDHexagonGrid2DCellComponent*> AFDHexagonGrid2D::GetAdjacentCells(FIntVector Coords)
{
	TArray<UFDHexagonGrid2DCellComponent*> AdjacentCells;

	UFDHexagonGrid2DCellComponent* Cell;

	if (IsValidCoords(Coords) && (Cell = GetCell(Coords))->IsValidLowLevelFast())
	{
		AdjacentCells.Add(Cell);
	}

	FIntVector AdjacentCoords;

	AdjacentCoords = Coords + FIntVector(0, 1, 0);
	if (IsValidCoords(AdjacentCoords) && (Cell = GetCell(AdjacentCoords))->IsValidLowLevelFast())
	{
		AdjacentCells.Add(Cell);
	}

	AdjacentCoords = Coords + FIntVector(0, -1, 0);
	if (IsValidCoords(AdjacentCoords) && (Cell = GetCell(AdjacentCoords))->IsValidLowLevelFast())
	{
		AdjacentCells.Add(Cell);
	}

	AdjacentCoords = Coords + FIntVector(1, 0, 0);
	if (IsValidCoords(AdjacentCoords) && (Cell = GetCell(AdjacentCoords))->IsValidLowLevelFast())
	{
		AdjacentCells.Add(Cell);
	}

	AdjacentCoords = Coords + FIntVector(-1, 0, 0);
	if (IsValidCoords(AdjacentCoords) && (Cell = GetCell(AdjacentCoords))->IsValidLowLevelFast())
	{
		AdjacentCells.Add(Cell);
	}

	if (Coords.X % 2 != 0)
	{
		AdjacentCoords = Coords + FIntVector(1, 1, 0);
		if (IsValidCoords(AdjacentCoords) && (Cell = GetCell(AdjacentCoords))->IsValidLowLevelFast())
		{
			AdjacentCells.Add(Cell);
		}

		AdjacentCoords = Coords + FIntVector(-1, 1, 0);
		if (IsValidCoords(AdjacentCoords) && (Cell = GetCell(AdjacentCoords))->IsValidLowLevelFast())
		{
			AdjacentCells.Add(Cell);
		}
	}
	else
	{
		AdjacentCoords = Coords + FIntVector(-1, -1, 0);
		if (IsValidCoords(AdjacentCoords) && (Cell = GetCell(AdjacentCoords))->IsValidLowLevelFast())
		{
			AdjacentCells.Add(Cell);
		}

		AdjacentCoords = Coords + FIntVector(1, -1, 0);
		if (IsValidCoords(AdjacentCoords) && (Cell = GetCell(AdjacentCoords))->IsValidLowLevelFast())
		{
			AdjacentCells.Add(Cell);
		}
	}

	return AdjacentCells;
}