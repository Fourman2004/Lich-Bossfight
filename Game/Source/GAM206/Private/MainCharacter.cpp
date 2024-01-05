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

	//creates spring arm to attach to root component of character.
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	//Camera is created and attached to spring arm
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);

	//staff is for First person view, is attached to camera.
	StaffMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaffMeshComponent");
	StaffMesh->SetupAttachment(CameraComp);

	//rotates character to the Player movement input
	GetCharacterMovement()->bOrientRotationToMovement = true;

	//bool to stop the player model from moving on the camera yaw
	bUseControllerRotationYaw = false;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	mana = 1;//sets mana to 100%
}

void AMainCharacter::MoveForward(float value)
{
	FVector ForwardVector = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);//gets player Movement on the X axis
	AddMovementInput(ForwardVector, value);//inputs forward movement
}

void AMainCharacter::MoveRight(float value)
{
	FVector RightVector = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);//gets player movement on Y axis
	AddMovementInput(RightVector, value); //inputs horizontal movement
}

void AMainCharacter::Sprint()//null funct. Was going to be for sprint function
{
	GetCharacterMovement()->MaxWalkSpeed = 600;//doubles player movement.
}

void AMainCharacter::walk()
{
	GetCharacterMovement()->MaxWalkSpeed = 300;//Sets it to be half running speed.
}


// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Majority of this code is taken from https://docs.unrealengine.com/4.26/en-US/ProgrammingAndScripting/ProgrammingWithCPP/CPPTutorials/FirstPersonShooter/3/)
void AMainCharacter::Fire()
{
	if (mana != 0)//checks if mana is above 0
	{
		if (projectileclass)//checks if the projectile is not null
		{
			FVector eyeLocation,shootV;//vectors for finding the shooting distance
			FRotator eyeRotation, shootR;///rotation of character for shooting

			GetActorEyesViewPoint(eyeLocation, eyeRotation);//

			shootR = eyeRotation;
			shootV =  eyeLocation + FTransform(shootR).TransformVector(staffTip);

			UWorld* world = nullptr;//gets the current level the player is in.
			world->GetWorld();
			if (world)//if it can detect the world, will execute code.
			{
				//the projectile
				APlayer_Projectile* projectile;

			    //any parameters that need to be met are within this variable.
				FActorSpawnParameters Projectparams;
				Projectparams.Owner = this;
				Projectparams.Instigator = GetInstigator();
				projectile = world->SpawnActor<APlayer_Projectile>(projectileclass, shootV, shootR, Projectparams);//spawns the projectile in the world, using the player rotation and location, along with any parameters.
				if (projectile)//if it's gets the spawned projectile, the following code is executed.
				{
					FVector launch = shootR.Vector();//gets the vector of the rotated player.
					projectile->LaunchInDirection(launch);
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("cannot get world"));//logs if it cannot get world.
			}
			mana = -0.01f;//removes 1% mana
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Shot Failed"));//logs if the shot has failed.
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Causes player to move on X and Y axis.
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	//engages and disengages sprinting.
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::walk);

	//gets camera input and allows player to look around
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);//causes the player to jump. Player has 3 jumps that can be held for 1 second.
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMainCharacter::Fire);//shoots magic bolt (projectile)
}
