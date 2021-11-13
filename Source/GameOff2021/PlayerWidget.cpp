// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"

void UPlayerWidget::TakeDamage_Implementation(float DamageTaken) {
	if (TotalHealth > 0) {
		float healthPercentage = CurrentHealth / TotalHealth;
		float damage = DamageTaken / TotalHealth;
		CurrentHealth = (healthPercentage - damage) * TotalHealth;
	}
}

void UPlayerWidget::RegenerateHealth_Implementation(float Regeneration) {
	if (TotalHealth > 0) {
		float healthPercentage = CurrentHealth / TotalHealth;
		float regeneration = Regeneration / TotalHealth;
		CurrentHealth = (healthPercentage + regeneration) * TotalHealth;
	}
}

void UPlayerWidget::LoseMana_Implementation(float ManaLost) {
	if (TotalMana > 0) {
		float percentage = CurrentMana / TotalMana;
		float damage = ManaLost / TotalMana;
		CurrentMana = (percentage - damage) * TotalMana;
	}
}

void UPlayerWidget::RegenerateMana_Implementation(float Regeneration) {
	if (TotalMana > 0) {
		float percentage = CurrentMana / TotalMana;
		float regeneration = Regeneration / TotalMana;
		CurrentMana = (percentage + regeneration) * TotalMana;
	}
}
