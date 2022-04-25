// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonTanks/Player/TankPawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public APawnBase
{
	GENERATED_BODY()

public:
	ATower();
	virtual void Tick(float DetlaTime) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowProtectedAccess = "true"))
	float range;

private:

	class ATankPawn* tank;

	FTimerHandle fire_rate_time_handle;
	float fire_rate;
	void CheckFire();

	bool Can_Fire();
};
