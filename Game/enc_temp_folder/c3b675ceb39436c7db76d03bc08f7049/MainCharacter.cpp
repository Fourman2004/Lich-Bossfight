// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Detour/DetourNavMeshQuery.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);

	StaffMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaffMeshComponent");
	StaffMesh->SetupAttachment(CameraComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	mana = 1;
}

void AMainCharacter::MoveForward(float value)
{
	FVector ForwardVector = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(ForwardVector, value);
}

void AMainCharacter::MoveRight(float value)
{
	FVector RightVector = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, value);
}

void AMainCharacter::Sprint()
{

}


// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Majority of this code is taken from https://docs.unrealengine.com/4.26/en-US/ProgrammingAndScripting/ProgrammingWithCPP/CPPTutorials/FirstPersonShooter/3/)
void AMainCharacter::Fire()
{
	if (mana != 0)
	{
		if (projectileclass)
		{
			FVector eyeLocation,shootV;
			FRotator eyeRotation, shootR;

			GetActorEyesViewPoint(eyeLocation, eyeRotation);

			shootR = eyeRotation;
			shootV =  eyeLocation + FTransform(shootR).TransformVector(staffTip);

			UWorld* world = nullptr;
			world->GetWorld();
			if (world)
			{
				APlayer_Projectile* projectile;
				FActorSpawnParameters Projectparams;
				Projectparams.Owner = this;
				Projectparams.Instigator = GetInstigator();
				projectile = world->SpawnActor<APlayer_Projectile>(projectileclass, shootV, shootR, Projectparams);
				if (projectile)
				{
					FVector launch = shootR.Vector();
					projectile->LaunchInDirection(launch);
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("cannot get world"));
			}
			mana = -0.1f;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Shot Failed"));
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMainCharacter::Fire);
}
