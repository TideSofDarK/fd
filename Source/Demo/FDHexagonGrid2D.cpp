// Fill out your copyright notice in the Description page of Project Settings.

#include "FDHexagonGrid2D.h"

// Sets default values
AFDHexagonGrid2D::AFDHexagonGrid2D()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	CellsRootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CellsRootSceneComponent"));
	CellsRootSceneComponent->SetupAttachment(RootComponent);

	//for (auto X = 0; X < GridWidth; X++)
	//{
	//	Cells.Add(FCellsArray());
	//	for (auto Y = 0; Y < GridHeight; ++Y)
	//	{
	//		float HalfWidth = SourceSize.X / 2;
	//		float YOffset = (sqrt(3) / 2 * SourceSize.X) * Y;
	//		if (X % 2 != 0)
	//		{
	//			YOffset += (sqrt(3) / 2 * HalfWidth);
	//		}

	//		//UFDHexagonGrid2DCellComponent* Cell = NewObject<UFDHexagonGrid2DCellComponent>(this, *FString("CellSpriteComponent" + FString::FromInt(X) + FString::FromInt(Y)));
	//		UFDHexagonGrid2DCellComponent* Cell = CreateDefaultSubobject<UFDHexagonGrid2DCellComponent>(*FString("CellSpriteComponent" + FString::FromInt(X) + FString::FromInt(Y)));
	//		Cell->SetupAttachment(RootComponent);
	//		Cell->SetSprite(CellSprite);
	//		Cell->OnClicked.AddDynamic(this, &AFDHexagonGrid2D::CellClicked);
	//		Cell->SetRelativeLocation(FVector4(HalfWidth * 3 / 2 * X, 0, YOffset));
	//		Cell->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	//		Cell->SetCoords(FIntVector(X, Y, 0));

	//		Cells[X].Add(Cell);
	//	}
	//}
}

void AFDHexagonGrid2D::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	UpdateGrid();
}

void AFDHexagonGrid2D::UpdateGrid()
{
	TArray<UFDHexagonGrid2DCellComponent*> Cells = GetCells();

	FVector2D SourceSize;

	if (Cells.Num() > 0)
	{
		SourceSize = Cells[0]->GetSprite()->GetSourceSize();
	}
	else
	{
		return;
	}

	int X = 0;
	int Y = 0;

	for (UFDHexagonGrid2DCellComponent* Cell : Cells)
	{
		float HalfWidth = SourceSize.X / 2;
		float YOffset = (sqrt(3) / 2 * SourceSize.X) * Y;
		if (X % 2 != 0)
		{
			YOffset += (sqrt(3) / 2 * HalfWidth);
		}

		Cell->SetCoords(FIntVector(X, Y, 0));
		Cell->SetCellType(Cell->GetCellType());
		Cell->SetRelativeLocation(FVector4(HalfWidth * 3 / 2 * X, 0, YOffset));

		X++;
		if (X == GridWidth && Y == GridHeight)
		{
			break;
		}
		if (X == GridWidth)
		{
			X = 0;
			Y++;
		}
		if (Y == GridHeight)
		{
			Y = 0;
		}
	}
}

// Called when the game starts or when spawned
void AFDHexagonGrid2D::BeginPlay()
{
	Super::BeginPlay();

	//UpdateGrid();
	TArray<UFDHexagonGrid2DCellComponent*> Cells = GetCells();
	for (UFDHexagonGrid2DCellComponent* Cell : Cells)
	{
		Cell->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		Cell->OnClicked.AddDynamic(this, &AFDHexagonGrid2D::CellClicked);
	}

	EnableInput(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void AFDHexagonGrid2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#if WITH_EDITOR
void AFDHexagonGrid2D::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void AFDHexagonGrid2D::CellClicked(UPrimitiveComponent* PrimitiveComponent, FKey Key)
{
	UFDHexagonGrid2DCellComponent* Cell = Cast<UFDHexagonGrid2DCellComponent>(PrimitiveComponent);
	if (Cell->IsValidLowLevelFast())
	{
		OnCellClickedDelegate.Broadcast(Cell);
	}
}

bool AFDHexagonGrid2D::IsValidCoords(FIntVector Coords)
{
	bool Contains = GetCells().ContainsByPredicate([&](const UFDHexagonGrid2DCellComponent* InItem)
	{
		return InItem->GetCoords() == Coords;
	});

	return Contains;
}

UFDHexagonGrid2DCellComponent* AFDHexagonGrid2D::GetCell(FIntVector Coords)
{
	UFDHexagonGrid2DCellComponent* Cell = *GetCells().FindByPredicate([&](const UFDHexagonGrid2DCellComponent* InItem)
	{
		return InItem->GetCoords() == Coords;
	});

	return Cell;
}

TArray<UFDHexagonGrid2DCellComponent*> AFDHexagonGrid2D::GetAdjacentCells(FIntVector Coords)
{
	TArray<UFDHexagonGrid2DCellComponent*> AdjacentCells;

	UFDHexagonGrid2DCellComponent* Cell = GetCell(Coords);

	if (IsValidCoords(Coords) && Cell->IsValidLowLevelFast())
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

TArray<UFDHexagonGrid2DCellComponent*> AFDHexagonGrid2D::GetCells()
{
	TArray<USceneComponent*> Children;
	CellsRootSceneComponent->GetChildrenComponents(true, Children);

	TArray<UFDHexagonGrid2DCellComponent*> AllCells;
	
	for (USceneComponent* SceneComponent : Children)
	{
		if (SceneComponent->IsA<UFDHexagonGrid2DCellComponent>())
		{
			AllCells.Add(Cast<UFDHexagonGrid2DCellComponent>(SceneComponent));
		}
	}

	return AllCells;
}