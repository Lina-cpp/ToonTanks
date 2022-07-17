// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

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

	//binding onhit() to OnHitComponent so we can do stuff on hit UwU
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//declaration of OnHit function
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	/*
	UE_LOG(LogTemp, Warning, TEXT("onhit!"));
	UE_LOG(LogTemp, Warning, TEXT("Hit comp: %s"), *HitComp->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Other actor: %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Other comp: %s"), *OtherComp->GetName());
	*/

	//setting instigator
	auto MyOwner = GetOwner();
	if(MyOwner == nullptr) return;

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClas = UDamageType::StaticClass();

	//setting projectiles to deal damage and destroying them
	if(OtherActor && OtherActor !=this && OtherActor != MyOwner)
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClas);
			Destroy();
		}


}