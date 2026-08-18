// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pistol.generated.h"

class UNiagaraSystem;
class USoundBase;
class USceneComponent;
class APistolProjectile;

UCLASS()
class CPPTEMPLATE_API APistol : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APistol();
	void Shot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Niagara System spawned at the ShotPoint component when firing. Pick it in the editor.
	UPROPERTY(EditAnywhere, Category = "VFX")
	TObjectPtr<UNiagaraSystem> MuzzleFlashEffect;

	UPROPERTY(Transient)
	TObjectPtr<USceneComponent> ShotPointComponent;

	void FindShotPointComponent();
	void SpawnProjectile();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
 	UPROPERTY(EditAnywhere, Category="Audio")
    USoundBase* FiringSound;

	// Rounds per minute
	UPROPERTY(EditAnywhere, Category = "Weapon", meta = (ClampMin = "1.0", UIMin = "1.0"))
	float FireRate = 600.f;

	// Projectile spawned when firing. Set to BP_PistolProjectile in the editor.
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<APistolProjectile> pistolProjectile;

	// How far the pistol kicks back (along its own local -X) when fired.
	UPROPERTY(EditAnywhere, Category = "Weapon|Recoil", meta = (ClampMin = "0.0"))
	float RecoilDistance = 3.f;

	// How quickly the pistol returns to its resting position after recoiling.
	UPROPERTY(EditAnywhere, Category = "Weapon|Recoil", meta = (ClampMin = "0.1"))
	float RecoilRecoverySpeed = 12.f;

	// How far the pistol rotates back (Roll, around its own local X axis) when fired.
	UPROPERTY(EditAnywhere, Category = "Weapon|Recoil", meta = (ClampMin = "0.0"))
	float RecoilRotationAngle = 45.f;

private:
	float LastFireTime = -FLT_MAX;

	// The root component's relative location/rotation before any recoil is applied - recoil offsets from here and eases back to it.
	FVector RestRelativeLocation = FVector::ZeroVector;
	FRotator RestRelativeRotation = FRotator::ZeroRotator;

};

