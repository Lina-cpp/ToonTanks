// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("Projectile mesh") );
		RootComponent = ProjectileMesh;		//Making it a root
	//Using UE to make our projectile move
	ProjectileMovementCom = CreateDefaultSubobject<UProjectileMovementComponent>( TEXT("Projectile Move. Comp."));
		ProjectileMovementCom->MaxSpeed = 1300.f;		//max proj. speed
		ProjectileMovementCom->InitialSpeed = 1300.f;	//speed at start


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

