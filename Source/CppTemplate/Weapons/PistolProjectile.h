// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PistolProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;
class UArrowComponent;
class UNiagaraSystem;

UCLASS()
class CPPTEMPLATE_API APistolProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APistolProjectile();

	// Root collision. Blocks everything - see NotifyHit. Ignoring the player is handled via
	// Collision Channels/Presets, not here.
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	TObjectPtr<USphereComponent> SphereCollider;

	// Drives the projectile forward. Requires the root component's Mobility to be Movable.
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	// Trail effect. Assign the Niagara System in the editor.
	UPROPERTY(VisibleAnywhere, Category = "VFX")
	TObjectPtr<UNiagaraComponent> Niagara;

	// Editor-only visualization of the projectile's forward direction.
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	TObjectPtr<UArrowComponent> Arrow;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called automatically by the engine on a blocking collision (no binding needed).
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	// Applies damage, spawns the hit effect, and destroys the projectile.
	void HandleImpact(AActor* OtherActor, const FVector& HitLocation);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 25.f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	TSubclassOf<UDamageType> DamageTypeClass;

	// Spawned at the hit location when the projectile hits something. Assign the Niagara System in the editor.
	UPROPERTY(EditAnywhere, Category = "VFX")
	TObjectPtr<UNiagaraSystem> HitEffect;



};
