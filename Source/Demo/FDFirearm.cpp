// Fill out your copyright notice in the Description page of Project Settings.

#include "FDFirearm.h"

AFDFirearm::AFDFirearm()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ShotAudioComp"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	if (ShotSound->IsValidLowLevelFast()) {
		AudioComponent->SetSound(ShotSound);
	}
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

	GetWorld()->LineTraceSingleByChannel(RV_Hit, GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * 1000), ECC_Pawn, RV_TraceParams);

	if (RV_Hit.bBlockingHit)
	{
		// TODO
		// Damage
		// Decals
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