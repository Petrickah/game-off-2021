#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum ESpellType {
	None	UMETA(DisplayName = "No Spell"),
	Fire	UMETA(DisplayName = "Fire Spell"),
	Water	UMETA(DisplayName = "Water Spell"),
	Ice		UMETA(DisplayName = "Ice Spell"),
	Earth	UMETA(DisplayName = "Earth Spell")
};