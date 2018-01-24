// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Delegates/DelegateCombinations.h"
#include "FDGameplayObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractDelegate, class AActor*, OtherActor);

UENUM(BlueprintType)
enum class EGameplayObjectState : uint8
{
	VE_DisabledVisible UMETA(DisplayName = "Disabled and Visible"),
	VE_EnabledVisible UMETA(DisplayName = "Enabled and Visible"),
	VE_DisabledHidden UMETA(DisplayName = "Disabled and Hidden"),
	VE_EnabledHidden UMETA(DisplayName = "Enabled and Hidden") // Probably useless
};

UCLASS()
class DEMO_API AFDGameplayObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFDGameplayObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** GetStaticMeshComponent **/
	FORCEINLINE class UStaticMeshComponent* GetStaticMeshComponent() { return StaticMeshComponent; }

	/** GetBoxComponent **/
	FORCEINLINE class UBoxComponent* GetBoxComponent() { return BoxComponent; }

	/** SetGameplayObjectState **/
	UFUNCTION(BlueprintCallable, Category = "Gameplay Object")
	virtual void SetGameplayObjectState(EGameplayObjectState NewGameplayObjectState);

	/** Interact */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Object")
	virtual void Interact(AActor* OtherActor);

	/** GetBypassNearestObjectDetection */
	UFUNCTION(BlueprintPure, Category = "Gameplay Object")
	bool GetBypassNearestObjectDetection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** SceneComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;

	/** StaticMeshComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;

	/** BoxComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	/** bBypassNearestObjectDetection */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Object")
	bool bBypassNearestObjectDetection;

	/** GameplayObjectState */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Object")
	EGameplayObjectState GameplayObjectState;

	/** OnInteract */
	UPROPERTY(BlueprintAssignable, Category = "Gameplay Object")
	FOnInteractDelegate OnInteractDelegate;
};
