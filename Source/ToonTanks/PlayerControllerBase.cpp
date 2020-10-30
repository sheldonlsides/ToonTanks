// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"


void APlayerControllerBase::IsPlayerEnabled(bool bSetPlayEnabled) 
{
    if (bSetPlayEnabled) {
        GetPawn()->EnableInput(this);
    } else {
        GetPawn()->DisableInput(this);
    }

    bShowMouseCursor = bSetPlayEnabled;
}
