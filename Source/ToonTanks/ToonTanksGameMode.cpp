// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

//what todo when actor dies
void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    //if tank dies
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();  //destroying tank
            if(ToonTanksPlayerController)
            {
                //enabling/disabling tank (can you move him or not)
                ToonTanksPlayerController->SetPlayerEnabledState(false);                
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

    //calling GameStartFunction
    HandleGameStart();   
}

//function that takes care about game starting
void AToonTanksGameMode::HandleGameStart()
{
    //setting tank pointer || this, cuz its THIS tank, 0 - player index
    Tank = Cast<ATank>( UGameplayStatics::GetPlayerPawn(this, 0) );
    //setting playerController pointer
    ToonTanksPlayerController = Cast<AToonTanksPlayerController> (UGameplayStatics::GetPlayerController(this, 0));

    if(ToonTanksPlayerController)
    {
        //diabling input, so we can't move the tank
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;

        //timer delegate || calling timer function with callback that requires value
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true
            );

        //setting timer
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
        PlayerEnableDelegate,
        StartDelay,
        false
        );
    }

}