// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	//sets default health
	Health = DefaultHealth;
    
	//gets reference to gamemode
	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//gets owner and applied the TakeDamage function to it
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser) 
{
	if(Damage == 0 || Health <= 0) {
		return;
	}

	//sets health and ensures that is not below zero or above the default health allowed
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	UE_LOG(LogTemp, Warning, TEXT("Health remaining %f"), Health);


	if (DamageCauser->GetClass() != DamagedActor->GetClass()) {
		//checks to see if the component has less than or equal zero health
		if (Health <= 0) {
			if(GameModeRef) {
				GameModeRef->ActorDied(GetOwner());
			} else {
				UE_LOG(LogTemp, Warning, TEXT("Health Component has no reference to the GameMode"));
			}
		}
	}
}
