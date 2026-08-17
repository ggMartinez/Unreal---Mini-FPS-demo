// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h" 
#include "PistolProjectile.h"

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

void APistolProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// Ignore the player - hardcoded tag check.
	if (OtherActor && OtherActor->ActorHasTag(TEXT("Player"))){
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Collided with player")));
		return;

	}

	const FString HitName = OtherActor ? OtherActor->GetName() : TEXT("Unknown");
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Collided")));
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Projectile hit: %s"), *HitName));


	UGameplayStatics::ApplyDamage(
		OtherActor,
		Damage,
		GetInstigatorController(),   // who gets the kill credit
		this,                        // damage causer (the projectile)
		DamageTypeClass
	);

	Destroy();
}

