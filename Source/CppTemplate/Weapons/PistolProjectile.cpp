// Fill out your copyright notice in the Description page of Project Settings.


#include "PistolProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/ArrowComponent.h"

// Sets default values
APistolProjectile::APistolProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->InitSphereRadius(5.f);
	SphereCollider->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	SetRootComponent(SphereCollider);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(SphereCollider);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 3500.f;
	ProjectileMovement->MaxSpeed = 3500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	Niagara->SetupAttachment(SphereCollider);

}

// Called when the game starts or when spawned
void APistolProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APistolProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APistolProjectile::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	HandleImpact(Other, HitLocation, HitNormal);
}

void APistolProjectile::HandleImpact(AActor* OtherActor, const FVector& HitLocation, const FVector& HitNormal)
{
	const FString HitName = OtherActor ? OtherActor->GetName() : TEXT("Unknown");

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Projectile hit: %s"), *HitName));

	UGameplayStatics::ApplyDamage(
		OtherActor,
		Damage,
		GetInstigatorController(),   // who gets the kill credit
		this,                        // damage causer (the projectile)
		DamageTypeClass
	);

	// Orient the effect to the hit surface (e.g. its Z axis points away from the surface) rather than
	// the projectile's travel direction, so it doesn't end up embedded in angled geometry.
	if (HitEffect)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, HitEffect, HitLocation, HitNormal.Rotation());

	// Stop moving/colliding immediately, but let the trail's existing particles fade out naturally
	// instead of cutting it off - Destroy() would kill the trail component instantly.
	SetActorEnableCollision(false);
	ProjectileMovement->StopMovementImmediately();
	if (Niagara)
		Niagara->Deactivate();

	SetLifeSpan(1.5f);
}

