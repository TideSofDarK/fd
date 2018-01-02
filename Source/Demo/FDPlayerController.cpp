// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FDPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FDCharacter.h"

AFDPlayerController::AFDPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AFDPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (!MyPawn)
	{
		MyPawn = Cast<AFDCharacter>(GetPawn());
	}

	USpringArmComponent* CameraBoom = MyPawn->GetCameraBoom();

	FRotator R1 = CameraBoom->GetTargetRotation();
	FRotator R2 = CameraBoom->GetTargetRotation();
	R2.Yaw = fCameraPitch;
	
	if ((R1 - R2).IsNearlyZero(1.0f))
	{
		bUpdateCamera = false;
	}

	CameraBoom->SetRelativeRotation(FMath::Lerp(R1, R2, 0.15f));
}

void AFDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	bUpdateCamera = false;
	fCameraPitch = -180.0f;

	InputComponent->BindAxis("MoveForward", this, &AFDPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFDPlayerController::MoveRight);
	InputComponent->BindAxis("Sprint", this, &AFDPlayerController::Sprint);

	InputComponent->BindAction("RotateCameraLeft", IE_Pressed, this, &AFDPlayerController::RotateCameraLeft);
	InputComponent->BindAction("RotateCameraRight", IE_Pressed, this, &AFDPlayerController::RotateCameraRight);
}

void AFDPlayerController::MoveForward(float Value)
{
	if ((Value != 0.0f) && !bUpdateCamera)
	{
		USpringArmComponent* CameraBoom = MyPawn->GetCameraBoom();

		const FRotator Rotation = CameraBoom->GetTargetRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		MyPawn->AddMovementInput(Direction, Value);
	}
}

void AFDPlayerController::MoveRight(float Value)
{
	if ((Value != 0.0f) && !bUpdateCamera)
	{
		USpringArmComponent* CameraBoom = MyPawn->GetCameraBoom();

		const FRotator Rotation = CameraBoom->GetTargetRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		MyPawn->AddMovementInput(Direction, Value); 
	}
}

void AFDPlayerController::Sprint(float Value)
{
	bSprint = FMath::CeilToFloat(Value) == 1.0f;

	if (MyPawn)
	{
		MyPawn->GetCharacterMovement()->MaxWalkSpeed = bSprint ? 1000.0f : 600.0f;
	}
}

void AFDPlayerController::RotateCameraLeft()
{
	fCameraPitch -= 90.0f;
	bUpdateCamera = true;
}

void AFDPlayerController::RotateCameraRight()
{
	fCameraPitch += 90.0f;
	bUpdateCamera = true;
}