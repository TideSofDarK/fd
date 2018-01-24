// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FDStaticInteractableObject.h"
#include "FDTerminal.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AFDTerminal : public AFDStaticInteractableObject
{
	GENERATED_BODY()
	
public:
	AFDTerminal();

	/** Tick */
	virtual void Tick(float DeltaTime) override;

	/** GetCameraComponent **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }

	/** GetCameraComponent **/
	FORCEINLINE class UStaticMeshComponent* GetScreenMeshComponent() const { return ScreenMeshComponent; }

	/** Interact */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Object")
	virtual void Interact(AActor* OtherActor) override;

protected:
	/** BeginPlay */
	virtual void BeginPlay() override;

private:
	/** CameraComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** ScreenMeshComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ScreenMeshComponent;
};
