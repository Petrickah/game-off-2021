// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"

static float Clamp(float value, float min, float max) {
	if (value < min) return min;
	else if (value > max) return max;
	else return value;
}

void UPlayerWidget::TakeDamage_Implementation(float DamageTaken) {
	if (TotalHealth > 0) {
		float healthPercentage = CurrentHealth / TotalHealth;
		float damage = DamageTaken / TotalHealth;
		CurrentHealth = Clamp((healthPercentage - damage) * TotalHealth, 0, TotalHealth);
	}
}

void UPlayerWidget::RegenerateHealth_Implementation(float Regeneration) {
	if (TotalHealth > 0) {
		float healthPercentage = CurrentHealth / TotalHealth;
		float regeneration = Regeneration / TotalHealth;
		CurrentHealth = Clamp((healthPercentage + regeneration) * TotalHealth, 0, TotalHealth);
	}
}

void UPlayerWidget::LoseMana_Implementation(float ManaLost) {
	if (TotalMana > 0) {
		float percentage = CurrentMana / TotalMana;
		float lost = ManaLost / TotalMana;
		CurrentMana = Clamp((percentage - lost) * TotalMana, 0, TotalMana);
	}
}

void UPlayerWidget::RegenerateMana_Implementation(float Regeneration) {
	if (TotalMana > 0) {
		float percentage = CurrentMana / TotalMana;
		float regeneration = Regeneration / TotalMana;
		CurrentMana = Clamp((percentage + regeneration) * TotalMana, 0, TotalMana);
	}
}
