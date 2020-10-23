// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"


void APawnTurret::BeginPlay() 
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
}

void APawnTurret::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
}


void APawnTurret::CheckFireCondition() 
{
    //check if player == null || is Dead

    //check If player is in range

    UE_LOG(LogTemp, Warning, TEXT("Check firing condition"));
}
