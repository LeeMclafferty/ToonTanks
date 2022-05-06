// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonTanks/Player/ToonTanksPlayerController.h"
#include "ToonTanksPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksPlayerController : public APlayerController
{
	GENERATED_BODY()

		AToonTanksPlayerController();

public:

	void SetControllerEnableState(bool is_player_enabled);
};
