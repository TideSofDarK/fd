// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FDCharacter.generated.h"

UCLASS()
class DEMO_API AFDCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFDCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

private:
	/** ShadowDecal */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShadowDecal;
};
