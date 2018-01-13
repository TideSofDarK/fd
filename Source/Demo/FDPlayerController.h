// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Delegates/DelegateCombinations.h"
#include "FDPickableObject.h"
#include "FDPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateNearestObjectDelegate, class AFDGameplayObject*, OtherActor);

UCLASS()
class AFDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFDPlayerController();

	// Returns nearest pickable object
	// FORCEINLINE class FDPickableObject* GetNearestPickableObject() const { return NearestPickableObject; }

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	UFUNCTION()
	void EndOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	class AFDPlayerCharacter* MyPawn;

	/** Movement and Camera */
	bool bUpdateCamera;
	bool bSprint;
	float fCameraPitch;

	FVector2D MovementInput;
	FVector2D CameraInput;

	/** Potentional interact target */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Nearest Object", meta = (AllowPrivateAccess = "true"))
	class AFDGameplayObject* NearestInteractableObject;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	virtual void BeginPlay() override;

	/** Controls */
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Sprint(float AxisValue);

	void Interact();
	void LoopInventory();

	void SetCameraPitch(float Pitch);
	void RotateCameraLeft();
	void RotateCameraRight();

	UFUNCTION(BlueprintCallable, Category = "Nearest Object")
	void UpdateNearestInteractableObject();

	/** Delegates */

	UPROPERTY(BlueprintAssignable, Category = "Nearest Object")
	FUpdateNearestObjectDelegate OnUpdateNearestInteractableObject;
};


