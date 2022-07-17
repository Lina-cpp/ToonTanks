// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();

	// Called to bind functionality to input || movement function
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	//function aka Getter to get private variable
	APlayerController* GetTankPlayerController() const { return TankPlayerController; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* ArmComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	//Tank movement speed
	UPROPERTY(EditAnywhere,Category = "Movement")
	float Speed = 200.f;
	//Rotation speed
	UPROPERTY(EditAnywhere,Category = "Movement")
	float TurnRate = 45.f;
	
	//Function to check pressed keys and set movement
	void Move(float Value);
	void Turn(float Value);

	APlayerController* TankPlayerController;
};
