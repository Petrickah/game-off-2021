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