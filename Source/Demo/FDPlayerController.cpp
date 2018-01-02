// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FDPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "FDCharacter.h"

AFDPlayerController::AFDPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AFDPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void AFDPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AFDPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFDPlayerController::MoveRight);
}

//Input functions
void AFDPlayerController::MoveForward(float Value)
{
	if ((Value != 0.0f))
	{
		AFDCharacter* MyPawn = Cast<AFDCharacter>(GetPawn());

		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		MyPawn->AddMovementInput(Direction, Value);
	}
}

void AFDPlayerController::MoveRight(float Value)
{
	if ((Value != 0.0f))
	{
		AFDCharacter* MyPawn = Cast<AFDCharacter>(GetPawn());

		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		MyPawn->AddMovementInput(Direction, Value);
	}
}