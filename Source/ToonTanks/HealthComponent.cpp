// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	//setting MaxHealth - can be changed in pawn BP
	Health = MaxHealth;

	//bound OnTakeAnyDamage to delegate
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	//setting gamemode default
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


//function checks damage taken
void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if(Damage <= 0.f) return;

	//substracting DMG value from HP
	Health -= Damage;

	//checking if HP is lower/equal to 0
	if(Health <= 0.f && ToonTanksGameMode)
		{
			//actor dies
			ToonTanksGameMode->ActorDied(DamagedActor);
		}






	//UE_LOG(LogTemp, Warning, TEXT("Health %f"), Health);
	
}