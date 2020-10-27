#include "TankGameModeBase.h"
#include "TankPawn.h"
#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay() 
{
    Super::BeginPlay();

    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) 
{
    if(DeadActor == PlayerTank) {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);
    } else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor)) {
        DestroyedTurret->HandleDestruction();

        //decrement because turret was destroyed and then check turret count
        if (--TargetTurrets == 0) {
            HandleGameOver(true);
        }
    }
}

void ATankGameModeBase::HandleGameStart() 
{
     //sets the number of enemy turrets in the gameworld
    TargetTurrets = GetTargetTurretCount();

    //sets the current player in the world to a variable. since this is a one player game the player is at index zero
    PlayerTank = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this,0));

    GameStart();
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    if (PlayerWon) {
        UE_LOG(LogTemp, Warning, TEXT("PLAYER WON!!"))
    }
    
    GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurretCount() 
{
     //gets an array of turret enemies
    TArray<AActor*> TurretActors;

    //gets all the actors in the world that are turrets
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);

    return TurretActors.Num();
}
