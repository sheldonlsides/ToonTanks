#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay() 
{
    
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) 
{
    UE_LOG(LogTemp, Warning, TEXT("A Pawn died"));
    DeadActor->Destroy();
}

void ATankGameModeBase::HandleGameStart() 
{
    
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    
}
