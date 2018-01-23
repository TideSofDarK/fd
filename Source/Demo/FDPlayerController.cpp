// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FDPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FDInventoryComponent.h"
#include "FDPlayerCharacter.h"
#include "FDPickableObject.h"
#include "FDStaticInteractableObject.h"

AFDPlayerController::AFDPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AFDPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

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
	bSprint = false;
	bStrafe = false;
	fCameraPitch = 0.0f;

	InputComponent->BindAxis("MoveForward", this, &AFDPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFDPlayerController::MoveRight);
	InputComponent->BindAxis("Sprint", this, &AFDPlayerController::Sprint);
	InputComponent->BindAxis("Strafe", this, &AFDPlayerController::Strafe);

	InputComponent->BindAction("Interact", IE_Pressed, this, &AFDPlayerController::Interact);
	InputComponent->BindAction("LoopInventory", IE_Pressed, this, &AFDPlayerController::LoopInventory);

	InputComponent->BindAction("RotateCameraLeft", IE_Pressed, this, &AFDPlayerController::RotateCameraLeft);
	InputComponent->BindAction("RotateCameraRight", IE_Pressed, this, &AFDPlayerController::RotateCameraRight);
}

void AFDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MyPawn = Cast<AFDPlayerCharacter>(GetPawn());
	
	UCapsuleComponent* CapsuleComponent = MyPawn->FindComponentByClass<UCapsuleComponent>();

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AFDPlayerController::BeginOverlap);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &AFDPlayerController::EndOverlap);

	fCameraPitch = FMath::RoundToFloat(MyPawn->GetActorRotation().Euler().Z / 90.0f) * 90.0f;
	SetCameraPitch(fCameraPitch);
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

void AFDPlayerController::Strafe(float Value)
{
	bStrafe = FMath::CeilToFloat(Value) == 1.0f;

	if (MyPawn && !bSprint)
	{
		MyPawn->GetCharacterMovement()->bOrientRotationToMovement = !bStrafe;
		MyPawn->GetCharacterMovement()->MaxWalkSpeed = bStrafe ? 375.0f : 600.0f;
	}
}

void AFDPlayerController::Interact()
{
	UFDInventoryComponent* InventoryComponent = MyPawn->FindComponentByClass<UFDInventoryComponent>();

	AFDPickableObject* ActiveInventoryItem = InventoryComponent->GetActiveItem();

	AFDPickableObject* PickableObject = Cast<AFDPickableObject>(NearestInteractableObject);

	bool ValidNearestInteractableObject = NearestInteractableObject != nullptr && NearestInteractableObject->IsValidLowLevelFast();
	bool ValidActiveInventoryItem		= ActiveInventoryItem != nullptr && ActiveInventoryItem->IsValidLowLevelFast();

	if (ValidNearestInteractableObject && ValidActiveInventoryItem)
	{
		AFDStaticInteractableObject* StaticInteractableObject = Cast<AFDStaticInteractableObject>(NearestInteractableObject);

		bool ValidStaticInteractableObject = StaticInteractableObject != nullptr && StaticInteractableObject->IsValidLowLevel();

		// Use item on some object
		if (ValidStaticInteractableObject && StaticInteractableObject->CanInteractWith(ActiveInventoryItem))
		{
			StaticInteractableObject->InteractWithItem(ActiveInventoryItem, MyPawn);
		}
		else // Rollback to generic interact if item can't be used 
		{
			NearestInteractableObject->Interact(MyPawn);
		}
	}
	else if (ValidNearestInteractableObject)
	{
		NearestInteractableObject->Interact(MyPawn);
	}
	else if (ValidActiveInventoryItem)
	{
		ActiveInventoryItem->Use(MyPawn);
	}

	UpdateNearestInteractableObject();
}

void AFDPlayerController::LoopInventory()
{
	UFDInventoryComponent* InventoryComponent = MyPawn->FindComponentByClass<UFDInventoryComponent>();
	InventoryComponent->LoopInventory();
}

void AFDPlayerController::SetCameraPitch(float Pitch)
{
	USpringArmComponent* CameraBoom = MyPawn->GetCameraBoom();

	FRotator NewRotation = CameraBoom->GetTargetRotation();
	NewRotation.Yaw = Pitch;

	CameraBoom->SetRelativeRotation(NewRotation);
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

void AFDPlayerController::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UpdateNearestInteractableObject();
}

void AFDPlayerController::EndOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UpdateNearestInteractableObject();
}

bool AFDPlayerController::IsStrafing()
{
	return bStrafe;
}

void AFDPlayerController::UpdateNearestInteractableObject()
{
	UCapsuleComponent* CapsuleComponent = MyPawn->FindComponentByClass<UCapsuleComponent>();

	TArray<AActor*> Actors;
	CapsuleComponent->GetOverlappingActors(Actors, TSubclassOf<AFDGameplayObject>());

	for (int32 Index = Actors.Num() - 1; Index != -1; --Index)
	{
		AFDGameplayObject* Actor = Cast<AFDGameplayObject>(Actors[Index]);
		if (Actor->IsValidLowLevelFast() && !Actor->GetBypassNearestObjectDetection())
		{
			NearestInteractableObject = Actor;
			OnUpdateNearestInteractableObject.Broadcast(NearestInteractableObject);
			return;
		}
	}

	NearestInteractableObject = nullptr;
	OnUpdateNearestInteractableObject.Broadcast(nullptr);
}