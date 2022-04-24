
#include "ToonTanks/Player/PawnBase.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"



APawnBase::APawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	capsule_component = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));
	RootComponent = capsule_component;

	base_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	base_mesh->SetupAttachment(capsule_component);

	turret_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turret_mesh->SetupAttachment(base_mesh);

	projectile_spawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Location"));
	projectile_spawn->SetupAttachment(turret_mesh);

}

void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

