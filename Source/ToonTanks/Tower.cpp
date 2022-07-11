// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    
    if(Tank)
    {   
        // Find the distance tower - tank
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());        
        // Check to see if the Tank is is range
        if(Distance <= FireRange)
        {   
            //If in range, rotate turrt toward tank
            RotateTurret(Tank->GetActorLocation());
        }

 
    }
}


void ATower::BeginPlay()
{
    Super::BeginPlay();

    //Getting access to the tank
    Tank = Cast<ATank>( UGameplayStatics::GetPlayerPawn(this, 0) );
}