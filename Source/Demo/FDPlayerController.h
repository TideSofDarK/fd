// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FDPlayerController.generated.h"

UCLASS()
class AFDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFDPlayerController();

protected:
	class AFDCharacter* MyPawn;

	bool bUpdateCamera;
	bool bSprint;
	float fCameraPitch;

	/** */
	FVector2D MovementInput;
	FVector2D CameraInput;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** */
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Sprint(float AxisValue);

	void RotateCameraLeft();
	void RotateCameraRight();
};


