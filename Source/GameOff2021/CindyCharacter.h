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
	UChildActorComponent* MagicCircle;

	class UCharacterMovementComponent* CharacterMovement;
	UPROPERTY(BlueprintReadOnly)
	class UCindyAnimator* CindyAnimator;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsDeath = false;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnRespawn(class APlayerStart* PlayerStart);

	UFUNCTION(BlueprintImplementableEvent)
	void Walk(bool IsWalking);

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

	// Movement
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void OnJump();
	void OnSprintEvent();
	void OnCrouchEvent();

	// Attack
	UFUNCTION(BlueprintPure)
	bool CanUseStaff();
};
