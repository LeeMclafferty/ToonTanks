// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonTanks/Framework/ToonTanksGameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AToonTanksGameModeBase
{
	GENERATED_BODY()

		AToonTanksGameMode();
public:

	void ActorDied(AActor* dead_actor);

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool has_won_game);

	UPROPERTY(BlueprintReadOnly)
	float start_delay;
private:

	class ATankPawn* tank;

	class AToonTanksPlayerController*  ttplayer_controller;

	void HandleGameStart();

	int32 target_towers;
	int32 GetTargetTowerCount();
};
