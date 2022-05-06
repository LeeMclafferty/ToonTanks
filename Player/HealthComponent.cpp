// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Player/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

#include "ToonTanks/Framework/ToonTanksGameMode.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	max_health = 100.f;
	current_health = 0.f;

}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	current_health = max_health;

	gamemode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));

	//When this components owner takes damage call DamageTaken
	if(GetOwner() != nullptr)
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

}


void UHealthComponent::DamageTaken(AActor* damaged_actor, float damage, const UDamageType* damage_type, class AController* instigator, AActor* damage_causer)
{
	//Bind this to the OnTakeAnyDamage() function of its owner.

	if (damage <= 0.f)
		return;

	current_health -= damage;
	if (current_health <= 1.f)
	{
		if(gamemode)
			gamemode->ActorDied(damaged_actor);
	}

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("%s health is %f"), *this->GetName(), current_health));
	
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

