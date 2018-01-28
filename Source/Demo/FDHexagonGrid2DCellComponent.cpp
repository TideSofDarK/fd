// Fill out your copyright notice in the Description page of Project Settings.

#include "FDHexagonGrid2DCellComponent.h"

UFDHexagonGrid2DCellComponent::UFDHexagonGrid2DCellComponent()
{
	//if (!CellSprite->IsValidLowLevel())
	//{
		const ConstructorHelpers::FObjectFinder<UPaperSprite> CellSpriteFinder(TEXT("/Game/Sprites/HexagonCell"));
		CellSprite = CellSpriteFinder.Object;
	//}

	//if (!WallCellSprite->IsValidLowLevel())
	//{
		const ConstructorHelpers::FObjectFinder<UPaperSprite> WallCellSpriteFinder(TEXT("/Game/Sprites/HexagonCellWall"));
		WallCellSprite = WallCellSpriteFinder.Object;
	//}

	//if (!TargetCellSprite->IsValidLowLevel())
	//{
		const ConstructorHelpers::FObjectFinder<UPaperSprite> TargetCellSpriteFinder(TEXT("/Game/Sprites/HexagonCellTarget"));
		TargetCellSprite = TargetCellSpriteFinder.Object;
	//}
}

#if WITH_EDITOR
void UFDHexagonGrid2DCellComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName() == "CellType")
	{
		SetCellType(CellType);
	}
}
#endif

void UFDHexagonGrid2DCellComponent::SetCellType(ECellType NewCellType)
{
	CellType = NewCellType;
	switch (CellType)
	{
	case ECellType::VE_Regular:
		SetSprite(CellSprite);
		break;
	case ECellType::VE_Target:
		SetSprite(TargetCellSprite);
		break;
	case ECellType::VE_Wall:
		SetSprite(WallCellSprite);
		break;
	default:
		break;
	}
}

void UFDHexagonGrid2DCellComponent::SetCellColor(int NewCellColor)
{
	CellColor = FMath::Clamp(NewCellColor, 0, 5);
}

void UFDHexagonGrid2DCellComponent::IncrementCellColor()
{
	CellColor++;
	if (CellColor >= 6)
	{
		CellColor = 0;
	}
}