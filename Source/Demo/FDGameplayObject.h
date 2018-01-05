// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FDGameplayObject.generated.h"

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
};
