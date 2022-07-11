// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Constructing a Capsule Component - hitbox
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>( TEXT("Capsule Collider") );
		RootComponent = CapsuleComp; //Making it a root

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("BaseMesh") );
		BaseMesh->SetupAttachment(CapsuleComp); // Attaching to Capsule	

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("Turret Mesh") );
		TurretMesh->SetupAttachment(BaseMesh); // Attaching to BaseMesh

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>( TEXT("Projectile Spawn Point") );
		ProjectileSpawnPoint->SetupAttachment(TurretMesh); // Attaching to TurretMesh
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	//calc the distance between cursor location and our turret mesh
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator( 0.f, ToTarget.Rotation().Yaw, 0.f );

	//setting turret mesh roatation || FMath::RInterpTo makes rotation smoother
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(), 
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			5.f)
		);
}

//shooting
void ABasePawn::Fire()
{
	//Getting Location and Rotation of Projectile
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	//Spawning projectile
	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);

	//DrawDebugSphere(GetWorld(),ProjectileSpawnPointLocation,25.f,12,FColor::Blue,false,3);
}