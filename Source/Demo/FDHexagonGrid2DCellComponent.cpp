// Fill out your copyright notice in the Description page of Project Settings.

#include "FDHexagonGrid2DCellComponent.h"

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