#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ProjectileBase.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

// Called when the game starts or when spawned
void APawnBase::BeginPlay()
{
	Super::BeginPlay();
}

void APawnBase::RotateTurret(FVector LookAtTarget) 
{	
	FVector LoaakAtTargetClean = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();

	// update turretMesh rotation to face toward the LookAttarget passed from the child class
	// Gets turret X & Y rotation
	FRotator TurretRotation = FVector(LoaakAtTargetClean - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire() 
{
	// Get ProjectileSpawnPoint Location && Rotation -> Spawn Projectile class at Location firing toward Rotation (Fire in the direction that turret is facing)
	
	//checks to see if projectile reference is valid
	if(ProjectileClass) {
		
		// sets current location of the projectile spawn (since it is attached to turret that will be the relative location)
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();

		// sets current rotation of the projectile spawn
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);

		TempProjectile->SetOwner(this);
	}
}

void APawnBase::HandleDestruction() 
{
	// Universal functionality
	// Play death effects particle, sound and camera shake
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());


	// Then do Child overrrides
	// Turret - Inform GameMode turret destroyed -> Destroy() self
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	// PlayerTank - Inform GameMode player tank destroyed -> Hide() all components && stop movement input

	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);
}

// Called every frame
void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

