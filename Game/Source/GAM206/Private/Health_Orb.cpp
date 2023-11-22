

// Fill out your copyright notice in the Description page of Project Settings.


#include "Health_Orb.h"

// Sets default values
AHealth_Orb::AHealth_Orb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHealth_Orb::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealth_Orb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

