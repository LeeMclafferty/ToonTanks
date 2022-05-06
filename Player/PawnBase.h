
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	APawnBase();

	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();

	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* capsule_component;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* base_mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* turret_mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* projectile_spawn;

	void RotateTurret(FVector target_location);
	
	UPROPERTY(EditDefaultsOnly,Category = "Combat")
	TSubclassOf<class AProjectile> projectile_class;

	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	class UParticleSystem* death_vfx;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	class USoundBase* death_sound;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	float death_sfx_volume;

	

};
