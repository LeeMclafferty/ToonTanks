// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/World/Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	projectile_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = projectile_mesh;

	pmovement_component = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	pmovement_component->InitialSpeed = 20.f;
	pmovement_component->MaxSpeed = 100.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

