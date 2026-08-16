// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pistol.generated.h"

class UNiagaraSystem;
class USoundBase;
class USceneComponent;

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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
 	UPROPERTY(EditAnywhere, Category="Audio")
    USoundBase* FiringSound;

	// Rounds per minute
	UPROPERTY(EditAnywhere, Category = "Weapon", meta = (ClampMin = "1.0", UIMin = "1.0"))
	float FireRate = 600.f;

private:
	float LastFireTime = -FLT_MAX;

};

