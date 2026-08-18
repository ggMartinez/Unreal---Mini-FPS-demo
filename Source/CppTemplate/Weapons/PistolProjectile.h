// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PistolProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;
class UArrowComponent;

UCLASS()
class CPPTEMPLATE_API APistolProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APistolProjectile();

	// Root collision. Overlap-only - see NotifyActorBeginOverlap.
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	TObjectPtr<USphereComponent> Sphere;

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

	// Called automatically by the engine when this actor starts overlapping another actor (no binding needed).
	// The projectile's collision (Sphere) is overlap-only rather than blocking, so this is used instead of NotifyHit.
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 25.f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	TSubclassOf<UDamageType> DamageTypeClass;



};
