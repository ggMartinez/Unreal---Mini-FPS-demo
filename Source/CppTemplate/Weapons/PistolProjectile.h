// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PistolProjectile.generated.h"

class UPrimitiveComponent;

UCLASS()
class CPPTEMPLATE_API APistolProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APistolProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called automatically by the engine when this actor's collision hits something (no binding needed - requires
	// "Simulation Generates Hit Events" on the colliding component). All 8 parameters below are mandatory: this is
	// a C++ virtual override of AActor::NotifyHit, so the signature must match the base declaration exactly or it
	// won't compile (and if you dropped "override", it would silently fail to ever be called by the engine).
	// Note this is NOT the same signature as UPrimitiveComponent::OnComponentHit (that delegate only has 5 params:
	// HitComp, OtherActor, OtherComp, NormalImpulse, Hit) - both are filled in by the same hit-resolution code in
	// AActor::DispatchBlockingHit, which is why they overlap so much, but NotifyHit carries a couple of extra ones.
	virtual void NotifyHit(
		UPrimitiveComponent* MyComp,		// This actor's own component that got hit (the "HitComp" side, i.e. our collider - e.g. the projectile's Sphere).
		AActor* Other,						// The other actor involved, or nullptr if this hit raw level geometry with no owning actor.
		UPrimitiveComponent* OtherComp,	// The specific component on Other that was hit (e.g. a mesh/capsule) - more precise than Other's name alone.
		bool bSelfMoved,					// True if this actor's own movement caused the hit; false if it was instead hit by something else moving into it.
		FVector HitLocation,				// World-space impact point - same value as Hit.ImpactPoint, just passed separately for convenience.
		FVector HitNormal,					// World-space surface normal at the impact point - same value as Hit.ImpactNormal, again for convenience.
		FVector NormalImpulse,				// Physics impulse applied at the hit; stays zero here since this actor isn't simulating physics.
		const FHitResult& Hit				// Full sweep/trace result - contains MyComp/OtherComp/Other again, plus distance, bone name, etc.
	) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	int damage;



};
