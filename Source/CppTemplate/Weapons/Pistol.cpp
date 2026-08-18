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

	RestRelativeLocation = RootComponent->GetRelativeLocation();
	RestRelativeRotation = RootComponent->GetRelativeRotation();
}


// Called every frame
void APistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EaseRecoil(DeltaTime);
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
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, MuzzleFlashEffect, ShotPointComponent->GetComponentLocation(), ShotPointComponent->GetComponentRotation());
	if (FiringSound) 
		UGameplayStatics::PlaySoundAtLocation(this, FiringSound, GetActorLocation());
	if (pistolProjectile && ShotPointComponent)
		SpawnProjectile();

	Recoil();
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


void APistol::Recoil()
{
	RootComponent->SetRelativeLocation(RestRelativeLocation - FVector(RecoilDistance, 0.f, 0.f));
	RootComponent->SetRelativeRotation(RestRelativeRotation + FRotator(RecoilRotationAngle, 0.f, 0.f)); // Pitch, around local Y
}

void APistol::EaseRecoil(float DeltaTime)
{
	if (!RootComponent->GetRelativeLocation().Equals(RestRelativeLocation, 0.01f))
		RootComponent->SetRelativeLocation(FMath::VInterpTo(RootComponent->GetRelativeLocation(), RestRelativeLocation, DeltaTime, RecoilRecoverySpeed));

	if (!RootComponent->GetRelativeRotation().Equals(RestRelativeRotation, 0.01f))
		RootComponent->SetRelativeRotation(FMath::RInterpTo(RootComponent->GetRelativeRotation(), RestRelativeRotation, DeltaTime, RecoilRecoverySpeed));
}
