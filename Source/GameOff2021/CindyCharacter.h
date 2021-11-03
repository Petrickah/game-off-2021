// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CindyCharacter.generated.h"

UCLASS()
class GAMEOFF2021_API ACindyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACindyCharacter();
	
	class UCharacterMovementComponent* CharacterMovement;

	UFUNCTION(BlueprintImplementableEvent)
	void Sprint(bool IsSprinting);

	UFUNCTION(BlueprintImplementableEvent)
	void ToggleCrouch(bool IsCrouching);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Movement")
	float NormalWalkSpeed;

	UPROPERTY(EditAnywhere, Category="Movement")
	float SprintWalkSpeed;

	bool Sprinting, Crouching;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void OnSprintEvent();
	void OnCrouchEvent();
};
