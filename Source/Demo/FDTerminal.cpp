#include "FDTerminal.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"

AFDTerminal::AFDTerminal()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);

	ScreenMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScreenMeshComponent"));
	ScreenMeshComponent->SetupAttachment(RootComponent);

	const ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMesh(TEXT("/Engine/BasicShapes/Plane"));
	ScreenMeshComponent->SetStaticMesh(PlaneMesh.Object);
}

void AFDTerminal::BeginPlay()
{
	Super::BeginPlay();

}

void AFDTerminal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFDTerminal::Interact(AActor* OtherActor)
{
	Super::Interact(OtherActor);

}