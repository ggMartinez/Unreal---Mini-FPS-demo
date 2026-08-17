// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PistolProjectile.h"

// Sets default values
APistol::APistol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APistol::BeginPlay()
{
	Super::BeginPlay();

	FindShotPointComponent();
}


// Called every frame
void APistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APistol::Shot(){
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	const float TimeBetweenShots = 60.f / FMath::Max(FireRate, 1.f);
	if (CurrentTime - LastFireTime < TimeBetweenShots)
		return;
	LastFireTime = CurrentTime;

	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Pew pew!"));

	if (MuzzleFlashEffect && ShotPointComponent)
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFlashEffect, ShotPointComponent, NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
	}

	if (FiringSound)
		UGameplayStatics::PlaySoundAtLocation(this, FiringSound, GetActorLocation());

	if (pistolProjectile && ShotPointComponent)
		SpawnProjectile();
}



void APistol::SpawnProjectile()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;						// Attribute the projectile to this pistol (damage causer, self-collision ignoring, etc).
	SpawnParams.Instigator = GetInstigator();		// Propagate the pawn that's firing (e.g. for kill-credit/damage logic).
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;	// If the muzzle point is overlapping something, nudge the spawn out instead of failing to spawn.

	// Spawn pistolProjectile (e.g. BP_PistolProjectile) at the muzzle's world location/rotation.
	GetWorld()->SpawnActor<APistolProjectile>(pistolProjectile, ShotPointComponent->GetComponentLocation(), ShotPointComponent->GetComponentRotation(), SpawnParams);
}

void APistol::FindShotPointComponent()
{
	TInlineComponentArray<USceneComponent*> SceneComponents;
	GetComponents(SceneComponents);
	for (USceneComponent* Component : SceneComponents)
	{
		if (Component->GetName().Contains(TEXT("ShotPoint")))
		{
			ShotPointComponent = Component;
			break;
		}
	}
}