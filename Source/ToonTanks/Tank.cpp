// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ATank::ATank()
{
    //Creating SpringArm and Camera Comp. for Tank
    ArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm Component"));
        ArmComponent->SetupAttachment(RootComponent);
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
        Camera->SetupAttachment(ArmComponent);

} 
// Called to bind functionality to input || movement function
void ATank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    //Text macro, name of the axis mapping || pointer to the object binding the action for - this tank || address we are binding
    PlayerInputComponent->BindAxis( TEXT("MoveForward"), this, &ATank::Move );
}


//Function to check pressed keys and set movement
void ATank::Move(float Value)
{
    UE_LOG(LogTemp, Display, TEXT("float value: %f"), Value);
}




/*
// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
*/