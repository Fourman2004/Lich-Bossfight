// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Projectile.h"
#include "Engine/World.h"


// Sets default values
APlayer_Projectile::APlayer_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//creating the Collider, the movement and the Prticle system of the player projectile.
	Collision = CreateDefaultSubobject<USphereComponent>("Collider");

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");

	ParticleSystem = CreateDefaultSubobject<UParticleSystem>("Particles");
}



// Called when the game starts or when spawned
void APlayer_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayer_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

