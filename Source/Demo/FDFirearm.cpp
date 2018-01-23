// Fill out your copyright notice in the Description page of Project Settings.

#include "FDFirearm.h"

AFDFirearm::AFDFirearm()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ShotAudioComp"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	MagazineCapacity = 10;
	Damage = 10;
}

void AFDFirearm::Fire()
{
	AudioComponent->Play();

	// Line trace 
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	FHitResult RV_Hit(ForceInit);

	// Apply recoil
	FVector Direction = GetHolder()->GetActorForwardVector() + FVector(FMath::RandRange(-0.025f, 0.025f), FMath::RandRange(-0.025f, 0.025f), FMath::RandRange(-0.025f, 0.025f));

	GetWorld()->LineTraceSingleByChannel(RV_Hit, GetActorLocation(), GetActorLocation() + (Direction * 2000), ECC_Pawn, RV_TraceParams);
	
	if (RV_Hit.bBlockingHit)
	{
		// TODO
		// Damage
		// Decals
		UE_LOG(LogTemp, Warning, TEXT("Location is %s"), *RV_Hit.ImpactPoint.ToString());
		OnFired.Broadcast(RV_Hit);
	}

	MagazineCapacity--;

	if (MagazineCapacity == 1)
	{
		DestroyAfterUse = true;
	}
}

void AFDFirearm::Use(AActor* User)
{
	Super::Use(User);

	Fire();
}

FText AFDFirearm::GetCountText()
{
	return FText::FromString(FString::FromInt(MagazineCapacity));
}