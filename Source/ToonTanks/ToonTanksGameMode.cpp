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
            //Tank destroyed - we lost
            GameOver(false);
    }
    //if tower dies
    else if( ATower* DestroyedTower = Cast<ATower>(DeadActor) )
    {
        DestroyedTower->HandleDestruction();
        //if turret is destroyed, number of turret -1
        --TargetTowers;
        //if all turrets are destroyed, game over
        if(TargetTowers == 0)
        {
            GameOver(true);
        }

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
    TargetTowers = GetTargetTowerCount();

    //setting tank pointer || this, cuz its THIS tank, 0 - player index
    Tank = Cast<ATank>( UGameplayStatics::GetPlayerPawn(this, 0) );
    //setting playerController pointer
    ToonTanksPlayerController = Cast<AToonTanksPlayerController> (UGameplayStatics::GetPlayerController(this, 0));

    //blueprint function
    StartGame();

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

int32 AToonTanksGameMode::GetTargetTowerCount()
{
    //Array of towers
    TArray<AActor*> Towers;
    //Counting the numeber of towers in the world
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();
}