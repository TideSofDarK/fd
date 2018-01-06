// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Delegates/DelegateCombinations.h"
#include "FDGameplayObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractDelegate, class AActor*, OtherActor);

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

	/** SetHidden **/
	UFUNCTION(BlueprintCallable, Category = "Gameplay Object")
	virtual void SetHidden(bool Hidden);

	/** Interact */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Object")
	virtual void Interact(AActor* OtherActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** SceneComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;

	/** StaticMeshComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;

	/** StaticMeshOverride */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMesh* StaticMeshOverride;

	/** OnInteract */
	UPROPERTY(BlueprintAssignable, Category = "Gameplay Object")
	FInteractDelegate OnInteract;
};
