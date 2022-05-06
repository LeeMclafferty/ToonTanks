// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Framework/ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

#include "ToonTanks/Player/TankPawn.h"
#include "Toontanks/AI/Tower.h"
#include "ToonTanks/Player/ToonTanksPlayerController.h"

AToonTanksGameMode::AToonTanksGameMode()
{
	start_delay = 3.f;
	target_towers = 0;
}


void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor* dead_actor)
{
	if (dead_actor == tank)
	{
		tank->HandleDestruction();
		if (ttplayer_controller)
		{
			ttplayer_controller->SetControllerEnableState(false);
		}
		GameOver(false);
	}
	else if (ATower* tower = Cast<ATower>(dead_actor))
	{
		tower->HandleDestruction();
		target_towers--;
		if (target_towers == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	target_towers = GetTargetTowerCount();
	// Setting pointers
	tank = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	ttplayer_controller = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ttplayer_controller)
	{
		if (tank)
		{
			ttplayer_controller->SetControllerEnableState(false);
			FTimerHandle player_enable_handle;
			FTimerDelegate enable_delegate = FTimerDelegate::CreateUObject(ttplayer_controller, &AToonTanksPlayerController::SetControllerEnableState, true);
			GetWorldTimerManager().SetTimer(player_enable_handle, enable_delegate, start_delay, false);
		}
	}
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> found_actors;
	//You have to pass in a UClass, not an object. So you can pass in a static class or TSubclass of.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), found_actors);
	return found_actors.Num();
}
