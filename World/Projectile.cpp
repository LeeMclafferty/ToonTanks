// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/World/Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	projectile_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = projectile_mesh;

	pmovement_component = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	pmovement_component->InitialSpeed = 1800.f;
	pmovement_component->MaxSpeed = 2000.f;

	damage = 25.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	projectile_mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* hit_comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector normal_impulse, const FHitResult& hit)
{
	auto my_owner = GetOwner();
	if (my_owner == nullptr) 
		return;

	auto my_owner_instigator = my_owner->GetInstigatorController();
	auto damage_type_class = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != my_owner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, this->damage, my_owner_instigator, this, damage_type_class);
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

