// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanks/Player/TankPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"



ATankPawn::ATankPawn()
{
	spring_arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	spring_arm->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(spring_arm);

	speed = 500.f;
	turn_rate = 120.f;
}

void ATankPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATankPawn::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATankPawn::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATankPawn::Attack);
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Error, TEXT("Controller not found in TankPawn class"));
	controller = Cast<APlayerController>(GetController());
	controller->bShowMouseCursor = true;

	//DrawDebugSphere(GetWorld(), (GetActorLocation() + FVector(0.f, 0.f, 200.f)), 100.f, 32, FColor::Red, true, 30.f);

}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (controller)
	{
		FInputModeGameAndUI input_mode;
		FHitResult hit_result;
		controller->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hit_result);

		controller->SetInputMode(input_mode);
		//DrawDebugSphere(GetWorld(), hit_result.ImpactPoint, 25.f, 12, FColor::Red, false, -1.f);
		RotateTurret(hit_result.ImpactPoint);
	}
}

void ATankPawn::HandleDestruction()
{
	Super::HandleDestruction();
	// hide actor and disable ticking so the player does not lose their view and become a spectator.
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATankPawn::Move(float value)
{
	//AddActorLocalOffset() moves an actor once. Call it on every frame while a direction key is held.
	//The function just moves the root component and everything follows.

	//Multiply by delta time so movement is not frame rate dependent. 
	FVector delta_location(0.f);
	delta_location.X = (value * GetWorld()->GetDeltaSeconds()) * speed;
	AddActorLocalOffset(delta_location, true);
}
	
void ATankPawn::Turn(float value)
{
	FRotator delta_rotation(0.f);
	delta_rotation.Yaw = (value * GetWorld()->GetDeltaSeconds()) * turn_rate;

	AddActorLocalRotation(delta_rotation, true);
}

void ATankPawn::Attack()
{
	Fire();
}
