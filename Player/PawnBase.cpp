
#include "ToonTanks/Player/PawnBase.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "ToonTanks/World/Projectile.h"



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

void APawnBase::RotateTurret(FVector target_location)
{
	//Get the direction you want to point by subtracting the target location by the turrets location then set the 
	//rotation


	FVector to_target = target_location - turret_mesh->GetComponentLocation();
	FRotator look_rotation(0.f, to_target.Rotation().Yaw, 0.f);

	turret_mesh->SetWorldRotation(look_rotation);
}

//Called in child classes.
void APawnBase::Fire()
{
	GetWorld()->SpawnActor<AProjectile>(projectile_class, projectile_spawn->GetComponentLocation(), projectile_spawn->GetComponentRotation());
}
