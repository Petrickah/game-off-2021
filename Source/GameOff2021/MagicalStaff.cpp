// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicalStaff.h"
#include "CindyAnimator.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMagicalStaff::AMagicalStaff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaffMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("StaffMesh"));
	StaffMesh->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}

void AMagicalStaff::SetStaffVisibility(bool Visibility) {
	SetActorHiddenInGame(!Visibility);
}

FTransform AMagicalStaff::GetRelativeTransform(USkeletalMeshComponent* SKMesh, USpringArmComponent* CameraBoom) {
	FRotator TargetRotation = CameraBoom->GetTargetRotation();
	FTransform SpellSocketTransform = SKMesh->GetSocketTransform("Spell");
	return FTransform(TargetRotation, SpellSocketTransform.GetLocation(), SpellSocketTransform.GetScale3D());
}

void AMagicalStaff::EquipStaff_Implementation(ACindyCharacter* StaffOwner) {
	if (!IsCasting) {
		this->SetStaffVisibility(!IsStaffEquiped);
		if (!IsStaffEquiped) {
			EquippingStaff(StaffOwner);
			FTransform OwnerRelativeTransform = StaffOwner->GetRootComponent()->GetRelativeTransform();
			FTransform SpellEffectTransform = FTransform(
				OwnerRelativeTransform.GetRotation(),
				FVector(.0f, .0f, -90.0f),
				OwnerRelativeTransform.GetScale3D()
			);
			ShowMagic(StaffOwner, SpellEffectTransform);
			IsStaffEquiped = true;
		}
		else IsStaffEquiped = false;
		StaffOwner->CindyAnimator->AttackEvent(IsStaffEquiped);
	}
	else IsCasting = false;
}

void AMagicalStaff::DestroyEffect_Implementation(ACindyCharacter* StaffOwner) {
	StaffOwner->StopMovement(false);
	StaffOwner->MagicCircle->DestroyComponent();
}

void AMagicalStaff::Attack_Implementation(ACindyCharacter* StaffOwner, UAnimMontage* AnimMontage, bool IsPrimary) {
	if (!IsStaffEquiped) return;
	auto AnimInstance = StaffOwner->GetMesh()->GetAnimInstance();
	if (!IsAttacking) {
		TScriptDelegate<FWeakObjectPtr> StopMontageDelegate;
		StopMontageDelegate.BindUFunction(this, "StopMontage");
		AnimInstance->OnMontageBlendingOut.AddUnique(StopMontageDelegate);
		StaffOwner->PlayAnimMontage(AnimMontage);
		IsAttacking = true;
	}
	else {
		IsAttacking = AnimInstance->Montage_IsPlaying(AnimInstance->GetCurrentActiveMontage());
	}
}

void AMagicalStaff::CastSpell_Implementation(ACindyCharacter* StaffOwner, ESpellType SpellType) {
	if (IsStaffEquiped) {
		IsCasting = (!IsCasting) ? true : false;
		if (IsCasting && !OnCooldown) {
			UAnimInstance* AnimInstance = StaffOwner->GetMesh()->GetAnimInstance();
			if (!AnimInstance->IsAnyMontagePlaying()) {
				StaffOwner->StopMovement(true);
			}
		}
	} else IsCasting = false;
}

void AMagicalStaff::ToggleStaff(ACindyCharacter* StaffOwner) {
	if (IsStaffEquiped) {
		if (!StaffOwner->Crouching) SetStaffVisibility(true);
		else SetStaffVisibility(false);
	}
}


// Called when the game starts or when spawned
void AMagicalStaff::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagicalStaff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (OnCooldown) {
		CooldownTimer -= CooldownTimer * DeltaTime;
		if (CooldownTimer <= 0.1f) {
			CooldownTimer = 0;
			OnCooldown = false;
		}
	}
}

