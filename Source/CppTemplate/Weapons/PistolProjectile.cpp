// Fill out your copyright notice in the Description page of Project Settings.


#include "PistolProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
APistolProjectile::APistolProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->InitSphereRadius(5.f);
	Sphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SetRootComponent(Sphere);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 3500.f;
	ProjectileMovement->MaxSpeed = 3500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	Niagara->SetupAttachment(Sphere);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Sphere);
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

