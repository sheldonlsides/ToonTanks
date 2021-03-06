// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat",  meta=(AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat",  meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move",  meta=(AllowPrivateAccess = "true"))
	float MovementSpeed = 8000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity",  meta=(AllowPrivateAccess = "true"))
	float Gravity = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage",  meta=(AllowPrivateAccess = "true"))
	float Damage = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects",  meta=(AllowPrivateAccess = "true"))
	UParticleSystemComponent* ParticleTrail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects",  meta=(AllowPrivateAccess = "true"))
	UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UCameraShake> HitShake;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	

};
