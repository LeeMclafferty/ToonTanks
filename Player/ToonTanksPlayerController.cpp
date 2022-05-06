// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Player/ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

AToonTanksPlayerController::AToonTanksPlayerController()
{

}

void AToonTanksPlayerController::SetControllerEnableState(bool is_player_enabled)
{
	if (is_player_enabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = is_player_enabled;
}
