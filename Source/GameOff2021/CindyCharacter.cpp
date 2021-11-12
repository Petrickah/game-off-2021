// Fill out your copyright notice in the Description page of Project Settings.


#include "CindyCharacter.h"
#include "CindyAnimator.h"
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
	CindyAnimator = nullptr;
}

// Called when the game starts or when spawned
void ACindyCharacter::BeginPlay()
{
	Super::BeginPlay();
	auto animator = GetMesh()->GetAnimInstance();
	if (animator) {
		CindyAnimator = CastChecked<UCindyAnimator>(animator);
	}
}

// Called every frame
void ACindyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(!bDisableMovement) {
		CindyAnimator->WalkEvent();
		Walk(CharacterMovement->Velocity.Size() > 0.1f);
		Sprint(Sprinting);
	}

	CindyAnimator->JumpEvent(CharacterMovement->IsFalling());
	CindyAnimator->CrouchEvent(Crouching);
}

bool ACindyCharacter::CanUseStaff() {
	if (Sprinting) return false;
	if (Crouching) return false;
	if (CharacterMovement->IsFalling()) return false;

	return true;
}

// Called to bind functionality to input
void ACindyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACindyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveToSide", this, &ACindyCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ACindyCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACindyCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACindyCharacter::OnJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACindyCharacter::StopJumping);
	
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACindyCharacter::OnSprintEvent);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACindyCharacter::OnSprintEvent);
	
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACindyCharacter::OnCrouchEvent);

	PlayerInputComponent->BindAction("SpellCast_Fire", IE_Pressed, this, &ACindyCharacter::FireSpell);
	PlayerInputComponent->BindAction("SpellCast_Water", IE_Pressed, this, &ACindyCharacter::WaterSpell);
	PlayerInputComponent->BindAction("SpellCast_Ice", IE_Pressed, this, &ACindyCharacter::IceSpell);
	PlayerInputComponent->BindAction("SpellCast_Earth", IE_Pressed, this, &ACindyCharacter::EarthSpell);

	PlayerInputComponent->BindAction("SpellCast_Fire", IE_Released, this, &ACindyCharacter::FireSpell);
	PlayerInputComponent->BindAction("SpellCast_Water", IE_Released, this, &ACindyCharacter::WaterSpell);
	PlayerInputComponent->BindAction("SpellCast_Ice", IE_Released, this, &ACindyCharacter::IceSpell);
	PlayerInputComponent->BindAction("SpellCast_Earth", IE_Released, this, &ACindyCharacter::EarthSpell);
}

void ACindyCharacter::FireSpell() {
	//AttackingSystem->OnSpellCast(ESpellType::Fire);
}

void ACindyCharacter::WaterSpell() {
	//AttackingSystem->OnSpellCast(ESpellType::Water);
}

void ACindyCharacter::IceSpell() {
	//AttackingSystem->OnSpellCast(ESpellType::Ice);
}

void ACindyCharacter::EarthSpell() {
	//AttackingSystem->OnSpellCast(ESpellType::Earth);
}

void ACindyCharacter::MoveForward(float AxisValue)
{
	FVector forwardVector = GetActorForwardVector();
	if (AxisValue < 0) CharacterMovement->MaxWalkSpeed = this->NormalWalkSpeed;
	else if (this->Sprinting) CharacterMovement->MaxWalkSpeed = this->SprintWalkSpeed;
	if (!bDisableMovement) {
		AddMovementInput(forwardVector, AxisValue);
	}
}

void ACindyCharacter::MoveRight(float AxisValue) {
	FVector rightVector = GetActorRightVector();
	if (!bDisableMovement) {
		AddMovementInput(rightVector, AxisValue);
	}
}

void ACindyCharacter::OnJump() {
	if (bDisableMovement) return;
	if (!CharacterMovement->IsFalling()) Jump();
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
	if (bDisableMovement) return;
	Crouching = Crouching ? false : true;
	float walkSpeed = Crouching ? CharacterMovement->MaxWalkSpeedCrouched : NormalWalkSpeed;
	CharacterMovement->MaxWalkSpeed = walkSpeed;

	ToggleCrouch(Crouching);
}