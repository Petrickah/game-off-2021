// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellType.h"
#include "Animation/AnimInstance.h"
#include "CindyCharacter.h"

#include "CindyAnimator.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2021_API UCindyAnimator : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void WalkEvent();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void JumpEvent(bool IsFalling);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CrouchEvent(bool IsCrouching);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AttackEvent(bool ReadyToAttack);

	UFUNCTION(BlueprintCallable)
	void GetVelocityAxis(ACindyCharacter* CindyCharacter, float& Forward, float& Right);
};
