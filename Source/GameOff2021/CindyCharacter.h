// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CindyCharacter.generated.h"

UCLASS()
class GAMEOFF2021_API ACindyCharacter : public ACharacter
{
	GENERATED_BODY()

	float fCurrentTimer;
	bool bDisableMovement = false;

public:
	// Sets default values for this character's properties
	ACindyCharacter();
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	class UAttackingSystemComponent* AttackingSystem;

	class UCharacterMovementComponent* CharacterMovement;
	class UCindyAnimator* CindyAnimator;

	UFUNCTION(BlueprintImplementableEvent)
	void Sprint(bool IsSprinting);

	UFUNCTION(BlueprintImplementableEvent)
	void ToggleCrouch(bool IsCrouching);

	UFUNCTION(BlueprintCallable)
	inline void StopMovement(bool IsStopped) { bDisableMovement = IsStopped; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Movement")
	float NormalWalkSpeed;

	UPROPERTY(EditAnywhere, Category="Movement")
	float SprintWalkSpeed;

public:	
	bool Sprinting, Crouching;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void OnJump();
	void OnSprintEvent();
	void OnCrouchEvent();
	void OnStaffEquipped();

	bool CanUseStaff();
	void EquipStaff();
	void OnAttack();
	void OnSecondaryAttack();
};
