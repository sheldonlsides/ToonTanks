#include "TankGameModeBase.h"
#include "TankPawn.h"
#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay() 
{
    Super::BeginPlay();

    //gets an array of turret enemies
    TArray<AActor*> TurretActors;

    //gets all the actors in the world that are turrets
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);

    //sets the number of enemy turrets in the gameworld
    TargetTurrets = TurretActors.Num();

    //sets the current player in the world to a variable. since this is a one player game the player is at index zero
    PlayerTank = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this,0));
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) 
{
    if(DeadActor == PlayerTank) {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);
    } else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor)) {
        DestroyedTurret->HandleDestruction();

        TArray<AActor*> TurretActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
        TargetTurrets = TurretActors.Num();

        if (TargetTurrets == 0) {
            HandleGameOver(true);
        }
    }

}

void ATankGameModeBase::HandleGameStart() 
{
    
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    if (PlayerWon) {
        UE_LOG(LogTemp, Warning, TEXT("Player won"));
    }
}
