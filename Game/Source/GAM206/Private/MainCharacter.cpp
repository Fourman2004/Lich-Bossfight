// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

void AMainCharacter::Fire_Projectile()
{
	if (HitScan)
	{

	}
	else
	{
		//Spawnparameters->Owner = this;
		//UWorld::SpawnActor(APlayer_Projectile::StaticClass(), AMainCharacter::GetActorTransform(), Spawnparameters);
	}
}


/*void regen_Mana()
{
	if (&AMainCharacter::mana)
	{
	 &AMainCharacter::mana;
	}
}*/

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMainCharacter::Fire_Projectile);
	//PlayerInputComponent->BindAction("Regen Mana", IE_Repeat, this, & AMainCharacter::regen_Mana);
}
