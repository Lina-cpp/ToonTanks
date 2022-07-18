// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h" 

//enabling/disabling player input depends if player is alive
void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if(bPlayerEnabled)
    {   
        //enable input for THIS(our Tank)
        GetPawn()->EnableInput(this);
    }

    else
    {
        //disble input for THIS(our Tank)
        GetPawn()->DisableInput(this);
    }
    //show or hide mouse cursor
    bShowMouseCursor = bPlayerEnabled;
}