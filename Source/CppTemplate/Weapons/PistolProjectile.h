// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PistolProjectile.generated.h"

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
