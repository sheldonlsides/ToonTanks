// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

private:
	void CheckFireCondition();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat",  meta=(AllowPrivateAccess = "true"))
	float FireRate = 2.0f;

	FTimerHandle FireRateTimerHandle;

public:
	// APawnTurret();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
