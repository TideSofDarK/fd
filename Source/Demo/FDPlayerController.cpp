// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FDPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FDCharacter.h"
#include "FDPickableObject.h"

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
	fCameraPitch = -180.0f;

	InputComponent->BindAxis("MoveForward", this, &AFDPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFDPlayerController::MoveRight);
	InputComponent->BindAxis("Sprint", this, &AFDPlayerController::Sprint);

	InputComponent->BindAction("Pickup", IE_Pressed, this, &AFDPlayerController::Pickup);

	InputComponent->BindAction("RotateCameraLeft", IE_Pressed, this, &AFDPlayerController::RotateCameraLeft);
	InputComponent->BindAction("RotateCameraRight", IE_Pressed, this, &AFDPlayerController::RotateCameraRight);
}

void AFDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MyPawn = Cast<AFDCharacter>(GetPawn());
	
	UCapsuleComponent* CapsuleComponent = MyPawn->FindComponentByClass<UCapsuleComponent>();

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AFDPlayerController::BeginOverlap);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &AFDPlayerController::EndOverlap);
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

void AFDPlayerController::Pickup()
{
	if (NearestPickableObject)
	{
		NearestPickableObject->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("BBB"));
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

void AFDPlayerController::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("BBB"));
	UpdateNearestPickableObject();
}

void AFDPlayerController::EndOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("EEE"));
	UpdateNearestPickableObject();
}

void AFDPlayerController::UpdateNearestPickableObject()
{
	TArray<AActor*> Actors;
	MyPawn->GetOverlappingActors(Actors, TSubclassOf<AFDPickableObject>());

	NearestPickableObject = Actors.Num() > 0 ? Cast<AFDPickableObject>(Actors.Last()) : nullptr;

	OnUpdateNearestPickableObject.Broadcast(NearestPickableObject);
}