// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2021_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Health")
	float TotalHealth = 100;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Health")
	float CurrentHealth = 100;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mana")
	float TotalMana = 100;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Mana")
	float CurrentMana = 100;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Events")
	void TakeDamage(float DamageTaken);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Events")
	void RegenerateHealth(float Regeneration);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Events")
	void LoseMana(float ManaLost);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Events")
	void RegenerateMana(float Regeneration);
};
