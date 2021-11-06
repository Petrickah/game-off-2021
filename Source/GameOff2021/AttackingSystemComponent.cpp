// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackingSystemComponent.h"
#include "CindyAnimator.h"
#include "CindyCharacter.h"

// Sets default values for this component's properties
UAttackingSystemComponent::UAttackingSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAttackingSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	CindyCharacter = this->GetOwner<ACindyCharacter>();
}


// Called every frame
void UAttackingSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UAttackingSystemComponent::OnSpellCast(ESpellType SpellType) {
	if(!CastingSpell) {
		CastingSpell = true;
		CastSpell.Broadcast(SpellType);
	}
	else CastingSpell = false;

	CindyCharacter->CindyAnimator->CastSpellEvent(SpellType, CastingSpell);
	
}

void UAttackingSystemComponent::OnEquipStaff() {
	if (!CindyCharacter->CanUseStaff()) return;
	if (!StaffEquiped) {
		EquippingStaff.Broadcast();
		StaffEquiped = true;
	} else StaffEquiped = false;
	EquipStaff.Broadcast(StaffEquiped);
}

void UAttackingSystemComponent::ToggleEquippedStaff(USkeletalMeshComponent* Staff) {
	if (StaffEquiped) {
		Staff->SetVisibility(false);
		if (!CindyCharacter->Crouching) Staff->SetVisibility(true);
	}
}

void UAttackingSystemComponent::OnAttack(bool IsPrimary) {
	if (StaffEquiped) {
		Attacking = Attacking ? false : true;
		if (IsPrimary) PrimaryAttack.Broadcast(Attacking);
		else SecondaryAttack.Broadcast(Attacking);
	}
}

