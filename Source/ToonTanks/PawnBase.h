// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;
class AProjectileBase;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()
	
private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	//VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileClass; //ensures only projectiles of type AProjectileBase can be used

public:
	// Sets default values for this pawn's properties
	APawnBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RotateTurret(FVector LookAtTarget);

	void Fire();
};
