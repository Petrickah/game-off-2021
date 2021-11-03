// Fill out your copyright notice in the Description page of Project Settings.


#include "CindyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACindyCharacter::ACindyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NormalWalkSpeed = 400.0f;
	SprintWalkSpeed = 600.0f;
	CharacterMovement = GetCharacterMovement();
	CharacterMovement->MaxWalkSpeed = NormalWalkSpeed;
	CharacterMovement->MaxWalkSpeedCrouched = 300;
}

// Called when the game starts or when spawned
void ACindyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACindyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACindyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACindyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveToSide", this, &ACindyCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ACindyCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACindyCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACindyCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACindyCharacter::StopJumping);
	
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACindyCharacter::OnSprintEvent);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACindyCharacter::OnSprintEvent);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACindyCharacter::OnCrouchEvent);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ACindyCharacter::OnCrouchEvent);
}

void ACindyCharacter::MoveForward(float AxisValue)
{
	FVector forwardVector = GetActorForwardVector();
	AddMovementInput(forwardVector, AxisValue);
}

void ACindyCharacter::MoveRight(float AxisValue) {
	FVector rightVector = GetActorRightVector();
	AddMovementInput(rightVector, AxisValue);
}

void ACindyCharacter::OnSprintEvent()
{
	if (Crouching) return;

	Sprinting = Sprinting ? false : true;
	float walkSpeed = Sprinting ? SprintWalkSpeed : NormalWalkSpeed;
	CharacterMovement->MaxWalkSpeed = walkSpeed;

	Sprint(Sprinting);
}

void ACindyCharacter::OnCrouchEvent()
{
	Crouching = Crouching ? false : true;
	float walkSpeed = Crouching ? CharacterMovement->MaxWalkSpeedCrouched : NormalWalkSpeed;
	CharacterMovement->MaxWalkSpeed = walkSpeed;

	ToggleCrouch(Crouching);
}