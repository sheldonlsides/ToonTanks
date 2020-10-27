// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTurret;
class ATankPawn;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

	//adding a pointer to the players tank
	ATankPawn* PlayerTank;

	int32 TargetTurrets = 0;
	
public:
	void  ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

};
