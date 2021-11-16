// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpellComponent.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEOFF2021_API USpellComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpellComponent();

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spell Properties")
	bool IsUnlocked;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spell Properties")
	float SpellCooldown;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spell Properties")
	float ManaNeeded;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Spell Properties")
	float ManaRemaining;

public:	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnCastSpell(float ManaAmmount);

	UFUNCTION(BlueprintCallable)
	inline void UnlockSpell() { IsUnlocked = true; }
};
