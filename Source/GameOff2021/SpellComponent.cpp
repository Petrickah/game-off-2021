// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellComponent.h"
#include "MagicalStaff.h"

// Sets default values for this component's properties
USpellComponent::USpellComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USpellComponent::OnCastSpell_Implementation(float ManaAmmount) {
	if (IsUnlocked) {
		auto owner = GetOwner<AMagicalStaff>();
		ManaRemaining = owner->CalculateManaRemaining(ManaAmmount, ManaNeeded);
		owner->SetOnCooldown(true, SpellCooldown);
	}
}

