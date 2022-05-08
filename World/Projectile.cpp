// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/World/Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "MatineeCameraShake.h"



AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	projectile_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = projectile_mesh;

	smoke_trail_particles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail System"));
	smoke_trail_particles->SetupAttachment(RootComponent);

	pmovement_component = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	pmovement_component->InitialSpeed = 1800.f;
	pmovement_component->MaxSpeed = 2000.f; UPROPERTY(EditDefaultsOnly, Category = "Combat")

	damage = 25.f;
	hit_sfx_vol = 1.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	projectile_mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if(launch_sound)
		UGameplayStatics::PlaySoundAtLocation(this, hit_sound, GetActorLocation(), GetActorRotation(), hit_sfx_vol);
		
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
		this->Destroy();

		if (hit_sound)
			UGameplayStatics::PlaySoundAtLocation(this, hit_sound, OtherActor->GetActorLocation(), OtherActor->GetActorRotation(), hit_sfx_vol);

		if (hit_cam_shake_class)
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(hit_cam_shake_class);
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

