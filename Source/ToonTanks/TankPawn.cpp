#include "TankPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
	Move();
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATankPawn::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &ATankPawn::CalculateRotateInput);
}

void ATankPawn::CalculateMoveInput(float value) 
{
	MoveDirection = FVector(value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void ATankPawn::CalculateRotateInput(float value) 
{
	float RotateAmount =  (value * 100)  * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
}

void ATankPawn::Move() 
{
	AddActorLocalOffset(MoveDirection, true);
}

void ATankPawn::Rotate() 
{
	AddActorLocalRotation(RotationDirection, true);
}
