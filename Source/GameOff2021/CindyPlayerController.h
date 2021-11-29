// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "PlayerWidget.h"
#include "CindyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2021_API ACindyPlayerController : public APlayerController
{
	GENERATED_BODY()

	bool bHealthOnCooldown = false;
	float fHealthCooldownTimer = 0.0f;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widgets")
	TSubclassOf<class UPlayerWidget> PlayerUI;

	UPlayerWidget* PlayerUIWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	class APlayerStart* PlayerStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mana")
	float ManageableMana = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mana")
	float ManaRegenerationRate = 1.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthRegenerationRate = 2.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthRegenerationCooldown = 2.0f;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool ReadMana(float& ManaPool);

	UFUNCTION(BlueprintCallable)
	void UpdateMana(float ManaRemaining);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float Health);
};
