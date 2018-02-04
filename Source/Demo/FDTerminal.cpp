#include "FDTerminal.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "FDIngameHUD.h"

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

	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "NO BINDING INPUT");
	if (InputComponent->IsValidLowLevel())
	{
		InputComponent->BindAction("Escape", IE_Pressed, this, &AFDTerminal::ZoomOut);
	}
}

void AFDTerminal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFDTerminal::Interact_Implementation(AActor* OtherActor)
{
	Super::Interact_Implementation(OtherActor);

	ZoomIn();
}

void AFDTerminal::ZoomIn()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* Pawn = PlayerController->GetPawn();
	PlayerController->DisableInput(PlayerController);

	AFDIngameHUD* HUD = Cast<AFDIngameHUD>(PlayerController->GetHUD());
	HUD->SlideOutHUD();

	EnableInput(PlayerController);

	PlayerController->SetViewTargetWithBlend(
		this,
		0.5,
		EViewTargetBlendFunction::VTBlend_Linear,
		1.0,
		true);
}

void AFDTerminal::ZoomOut()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* Pawn = PlayerController->GetPawn();
	PlayerController->EnableInput(PlayerController);

	AFDIngameHUD* HUD = Cast<AFDIngameHUD>(PlayerController->GetHUD());
	HUD->SlideOutHUD();

	DisableInput(PlayerController);

	PlayerController->SetViewTargetWithBlend(
		PlayerController->GetPawn(),
		0.5,
		EViewTargetBlendFunction::VTBlend_Linear,
		1.0,
		true);
}