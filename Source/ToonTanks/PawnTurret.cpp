#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "TankPawn.h"

void APawnTurret::BeginPlay() 
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    //gets reference to player pawn
    PlayerPawn = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction() 
{
    Super::HandleDestruction();
    UE_LOG(LogTemp, Warning, TEXT("Destroyed turret"));
    Destroy();
}

void APawnTurret::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    if (!PlayerPawn || ReturnDistanceToPlayer() >= TurretFiringRange) {
        return;
    }

    RotateTurret(PlayerPawn->GetActorLocation());
}


void APawnTurret::CheckFireCondition() 
{
    //check if player == null || is Dead
    if(!PlayerPawn){
        return;
    }

    //check If player is in firing range
    if(ReturnDistanceToPlayer() <= TurretFiringRange){
       Fire();
    }
}

void Fire() {
     UE_LOG(LogTemp, Warning, TEXT("Turret firing at player"));
}

float APawnTurret::ReturnDistanceToPlayer() 
{
    if(!PlayerPawn){
        return 0.0f;
    }

    //PlayerPawn->GetActorLocation() - gets the location to the player pawn refernce
    //GetActorLocation() - gets location of current class object (turret)

    //returns the distance of the turrent to the player
    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}
