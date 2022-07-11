// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if( InFireRange() )
    {
        RotateTurret(Tank->GetActorLocation());
    }
}


void ATower::BeginPlay()
{
    Super::BeginPlay();

    //Getting access to the tank
    Tank = Cast<ATank>( UGameplayStatics::GetPlayerPawn(this, 0) );

    //Timer
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}


void ATower::CheckFireCondition()
{
    if(InFireRange())
    {
        Fire();
    }
}

bool ATower::InFireRange()
{
    if(Tank)
    {
        //checking the distance
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        //if in range
        if(Distance <= FireRange)
        {   
            return true;
        }
    }

    return false;
}