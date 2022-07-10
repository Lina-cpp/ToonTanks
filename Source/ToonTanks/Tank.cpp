// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

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
    //Turning left/right
    PlayerInputComponent->BindAxis( TEXT("Turn"), this, &ATank::Turn );
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(PlayerControllerRef) //checking if we possessed the controller
    {
        FHitResult HitResult;
        PlayerControllerRef->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility, 
            false,
            HitResult);
            
        //drawing sphere under cursor
        //DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,10.f,5,FColor::Blue,false,-1.f);

        RotateTurret(HitResult.ImpactPoint);

    }

}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
    PlayerControllerRef = Cast<APlayerController>( GetController() );

}


//Function to check pressed keys and set movement
void ATank::Move(float Value)
{
    FVector DeltaLocation = FVector::ZeroVector; //Puts vector to 0 0 0
    DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this); //Movement * value(1 or -1 axis) * speed * deltatime
    AddActorLocalOffset(DeltaLocation, true); // Actor will move in his own gizmo direction
}

//Function to turn right/left
void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator; //0ing rotator to 0
    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);
}