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

	//creating blueprint function
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	//function to decide if we won or lost
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:

	//getting TankPawn location
	class ATank* Tank;

	class AToonTanksPlayerController *ToonTanksPlayerController; 

	//Delay after which we start the game
	UPROPERTY(EditAnywhere)
	float StartDelay = 3.f;

	//function that takes care about game starting
	void HandleGameStart();

	//numbers of turrets
	int32 TargetTowers = 0;
	//how many turrets exists
	int32 GetTargetTowerCount();

};
