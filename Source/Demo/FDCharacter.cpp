// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FDCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"

AFDCharacter::AFDCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	ShadowDecal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShadowDecal"));
	ShadowDecal->SetupAttachment(GetCapsuleComponent());
	ShadowDecal->SetRelativeScale3D(FVector(0.9, 0.9, 0.125));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AFDCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ShadowDecal != nullptr)
	{
		FVector OutPosition;
		FRotator OutRotation;

		GetMesh()->TransformFromBoneSpace("ik_foot_root", FVector::ZeroVector, FRotator::ZeroRotator, OutPosition, OutRotation);

		OutPosition.Z = 0.0f;

		ShadowDecal->SetWorldLocation(OutPosition);
	}
}