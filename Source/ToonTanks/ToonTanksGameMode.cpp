// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

//what todo when actor dies
void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    //if tank dies
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();  //destroying tank
            if(Tank->GetTankPlayerController())
            {
                Tank->DisableInput(Tank->GetTankPlayerController());       //disabling movement
                Tank->GetTankPlayerController()->bShowMouseCursor = false; //turning off cursor
            }
    }
    //if tower dies
    else if( ATower* DestroyedTower = Cast<ATower>(DeadActor) )
    {
        DestroyedTower->HandleDestruction();
    }
    
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    //getting player pawn || this, cuz its THIS tank, 0 - player index
    Tank = Cast<ATank>( UGameplayStatics::GetPlayerPawn(this, 0) );
}