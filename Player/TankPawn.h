// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonTanks/Player/PawnBase.h"
#include "TankPawn.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankPawn : public APawnBase
{
	GENERATED_BODY()

public:

	ATankPawn();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// Call the super from pawn base here.
	void HandleDestruction();

	APlayerController* GetTankController() { return controller; }

protected:

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowProtectedAccess = "true"))
	float speed;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowProtectedAccess = "true"))
	float turn_rate;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowProtectedAccess = "true"))
	float fire_rate;

private:

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent* spring_arm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* camera;

	void Move(float value);
	void Turn(float value);
	void Attack();

	class APlayerController* controller;
	
};
