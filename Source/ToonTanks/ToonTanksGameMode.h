// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	//what todo when actor dies
	void ActorDied(AActor* DeadActor);

protected:

	virtual void BeginPlay() override;

private:

	//getting TankPawn location
	class ATank* Tank;

	class AToonTanksPlayerController *ToonTanksPlayerController; 

	//Delay after which we start the game
	UPROPERTY(EditAnywhere)
	float StartDelay = 3.f;

	//function that takes care about game starting
	void HandleGameStart();

};
