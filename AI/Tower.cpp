// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/AI/Tower.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#include "ToonTanks/Player/TankPawn.h"


ATower::ATower()
{
	range = 300.f;
	fire_rate = 2.f;
}

void ATower::Tick(float DetlaTime)
{
	Super::Tick(DetlaTime);

	if (Can_Fire())
	{
		// Point Turret at player
		RotateTurret(tank->GetActorLocation());
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	tank = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	GetWorld()->GetTimerManager().SetTimer(fire_rate_time_handle, this, &ATower::CheckFire, fire_rate, true);
}

void ATower::CheckFire()
{
	if (Can_Fire())
	{
		Fire();
	}
}

bool ATower::Can_Fire()
{
	//If Tank is valid
	if (tank)
	{
		// Get the Distance from the turret to the player
		float dist_to_tank = FVector::Dist(GetActorLocation(), tank->GetActorLocation());

		// Check if the player is in the range
		if (dist_to_tank <= range)
		{
			return true;
		}
	}
	
	return false;
}
