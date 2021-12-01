// Fill out your copyright notice in the Description page of Project Settings.


#include "CindyPlayerController.h"
#include "CindyCharacter.h"
#include "PlayerWidget.h"

void ACindyPlayerController::BeginPlay() {
	Super::BeginPlay();

	if (PlayerUI) {
		PlayerUIWidget = CreateWidget<UPlayerWidget>(this, PlayerUI);
		if (PlayerUIWidget) {
			PlayerUIWidget->AddToViewport();
		}
		bShowMouseCursor = false;
	}
}

void ACindyPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (GetPawn() != nullptr) {
		PlayerUIWidget->RegenerateMana(ManaRegenerationRate * DeltaTime);
		if (bHealthOnCooldown) {
			fHealthCooldownTimer -= DeltaTime;
			if (fHealthCooldownTimer <= 0) {
				fHealthCooldownTimer = 0;
				bHealthOnCooldown = false;
			}
		}
		else {
			PlayerUIWidget->RegenerateHealth(HealthRegenerationRate * DeltaTime);
		}

		if (PlayerUIWidget->CurrentHealth <= 0.1f) {
			ACindyCharacter* ControlledPawn = Cast<ACindyCharacter>(GetPawn());
			if (ControlledPawn != nullptr)
				ControlledPawn->OnDeath();
		}
	}
	else {
		PlayerStart->K2_OnReset();
	}
}

bool ACindyPlayerController::ReadMana(float& ManaPool) {
	if (PlayerUIWidget->CurrentMana > ManageableMana) {
		ManaPool = PlayerUIWidget->CurrentMana;
		return true;
	}
	return false;
}

void ACindyPlayerController::UpdateMana(float ManaRemaining) {
	float ManaUsed = ManaRemaining - PlayerUIWidget->CurrentMana;
	if (ManaUsed < 0) {
		PlayerUIWidget->LoseMana(-1.0f * ManaUsed);
	}
	else {
		PlayerUIWidget->RegenerateMana(+1.0f * ManaUsed);
	}
}

float ACindyPlayerController::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) {
	PlayerUIWidget->TakeDamage(DamageAmount);
	bHealthOnCooldown = true;
	fHealthCooldownTimer = HealthRegenerationCooldown;
	return DamageAmount;
}

void ACindyPlayerController::UpdateHealth(float Health) {
	if(PlayerUIWidget != nullptr)
		PlayerUIWidget->RegenerateHealth(Health);
}