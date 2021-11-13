// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerWidget.h"
#include "CindyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2021_API ACindyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widgets")
	TSubclassOf<class UPlayerWidget> PlayerUI;

	UPlayerWidget* PlayerUIWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mana")
	float ManageableMana = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mana")
	float ManaRegenerationRate = 1.2f;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool ReadMana(float& ManaPool);

	UFUNCTION(BlueprintCallable)
	void UpdateMana(float ManaRemaining);
};
