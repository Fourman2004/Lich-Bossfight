// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Player_Projectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystem;

UCLASS()
class GAM206_API APlayer_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayer_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UProjectileMovementComponent* ProjectileMovement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UParticleSystem* ParticleSystem;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

/*
Source: https://docs.unrealengine.com/5.3/en-US/implementing-projectiles-in-unreal-engine/
*/