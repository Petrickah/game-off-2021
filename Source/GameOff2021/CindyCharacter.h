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
	bool bHasStaffEquipping = false, bDisableMovement = false;

public:
	// Sets default values for this character's properties
	ACindyCharacter();
	
	class UCharacterMovementComponent* CharacterMovement;

	UFUNCTION(BlueprintImplementableEvent)
	void Sprint(bool IsSprinting);

	UFUNCTION(BlueprintImplementableEvent)
	void ToggleCrouch(bool IsCrouching);

	UFUNCTION(BlueprintImplementableEvent)
	void EquipStaff(bool HasStaff);

	UFUNCTION(BlueprintImplementableEvent)
	void EquippingStaff(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void FreezeMovement(float DeltaTime, float Duration);

	UFUNCTION(BlueprintPure)
	float GetDisableMovementDuration();

	UFUNCTION(BlueprintPure)
	bool IsMovementDisabled();

	UFUNCTION(BlueprintCallable)
	void StopEquippingStaff();

	UFUNCTION(BlueprintCallable)
	void ToggleEquippedStaff(class USkeletalMeshComponent* Staff);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Movement")
	float NormalWalkSpeed;

	UPROPERTY(EditAnywhere, Category="Movement")
	float SprintWalkSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DisableMovementDuration = 2.0f;

	bool Sprinting, Crouching, StaffEquiped = false;

public:	
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
};
