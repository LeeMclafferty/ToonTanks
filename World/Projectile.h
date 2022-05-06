// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "sfx")
	class USoundBase* launch_sound;

	UPROPERTY(EditDefaultsOnly, Category = "sfx")
	class USoundBase* hit_sound;

	UPROPERTY(EditDefaultsOnly, Category = "sfx")
	float hit_sfx_vol;

private:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* projectile_mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UProjectileMovementComponent* pmovement_component;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* hit_comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector normal_impulse, const FHitResult& hit);

	UPROPERTY(EditAnywhere)
	float damage;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* smoke_trail_particles;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* hit_particles;
};
