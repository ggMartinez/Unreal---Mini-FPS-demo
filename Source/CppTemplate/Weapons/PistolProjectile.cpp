// Fill out your copyright notice in the Description page of Project Settings.


#include "PistolProjectile.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
APistolProjectile::APistolProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	// Ignore hits against the player - hardcoded since the tag-based IgnoreActorWhenMoving approach wasn't working.
	if (Other && Other->ActorHasTag(TEXT("Player")))
		return;

	const FString HitName = OtherComp ? OtherComp->GetName() : (Other ? Other->GetName() : TEXT("Unknown"));

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Projectile hit: %s"), *HitName));

	Destroy();
}

