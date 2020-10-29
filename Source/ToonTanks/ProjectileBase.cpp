// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));

	RootComponent = ProjectileMesh;

	//no need to attach projectile movement conponents to anything
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovement->InitialSpeed = 5000.0f;
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->ProjectileGravityScale = Gravity;
	ProjectileMovement->bRotationFollowsVelocity = true;
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	//function to detect what actor was hit in the world
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	AActor* MyOwner = GetOwner();
	
	//get the string value name of the class of attacking actor
	FString ActorSendingDamage = GetOwner()->GetClass()->GetDefaultObjectName().ToString();
	// UE_LOG(LogTemp, Warning, TEXT("Actor Sending damage is %s"), *ActorSendingDamage);

	//get the string value name of the class being attacked
	FString ActorRecievingDamage = OtherActor->GetClass()->GetDefaultObjectName().ToString(); 
	// UE_LOG(LogTemp, Warning, TEXT("Actor Receiving damage by %s"), *ActorRecievingDamage);

	// logic check to make sure projectile can't cause damage to itself
	// OR logic checks to make sure friendly fire doesn't occur between enemy turrets
	if (!MyOwner || (ActorSendingDamage == ActorRecievingDamage)){
		Destroy();
		return;
	}

	//checks to ensure not colliding with self and not colliding with the parent that created the projectile
	if (OtherActor && OtherActor != this && OtherActor != MyOwner) {
		//applies damage to another actor in the world
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);

		Destroy();
	}
}
