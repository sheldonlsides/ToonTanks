#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void APawnTurret::BeginPlay() 
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    //gets reference to player pawn
    PlayerPawn = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
}


void APawnTurret::CheckFireCondition() 
{
    //check if player == null || is Dead
    if(!PlayerPawn){
        return;
    }

    //check If player is in firing range
    if(ReturnDistanceToPlayer() <= TurrentFiringRange){
        UE_LOG(LogTemp, Warning, TEXT("Player is in firing range"));
    }
}

float APawnTurret::ReturnDistanceToPlayer() 
{
    if(!PlayerPawn){
        return 0.0f;
    }

    //PlayerPawn->GetActorLocation() - gets the location to the player pawn refernce
    //GetActorLocation() - gets location of current class object (turret)

    //returns the distance of the turrent to the player
    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation())
}
