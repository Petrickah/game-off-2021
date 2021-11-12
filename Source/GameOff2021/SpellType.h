#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum ESpellType {
	None		UMETA(DisplayName = "No Spell"),
	Fire		UMETA(DisplayName = "Fire Spell"),
	Water		UMETA(DisplayName = "Water Spell"),
	Lightning	UMETA(DisplayName = "Lightning Spell"),
	Arcane		UMETA(DisplayName = "Arcane Spell")
};