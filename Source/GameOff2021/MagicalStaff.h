// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CindyCharacter.h"
#include "SpellType.h"
#include "MagicalStaff.generated.h"

UCLASS()
class GAMEOFF2021_API AMagicalStaff : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicalStaff();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class USkeletalMeshComponent* StaffMesh;

protected:

	UPROPERTY(BLueprintReadWrite, VisibleAnywhere)
	float CooldownTimer = 0.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool IsStaffEquiped = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool IsAttacking = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool IsCasting = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool OnCooldown = false;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DestroyEffect(ACindyCharacter* StaffOwner);

	UFUNCTION(BlueprintImplementableEvent)
	void StopMontage(UAnimMontage* Montage, bool Interrupted);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetStaffVisibility(bool Visibility);

	UFUNCTION(BlueprintCallable)
	void ToggleStaff(ACindyCharacter* StaffOwner);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EquipStaff(ACindyCharacter* StaffOwner);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ShowMagic(ACindyCharacter* StaffOwner, FTransform RelativeTransform);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void EquippingStaff(ACindyCharacter* StaffOwner);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Attack(ACindyCharacter* StaffOwner, UAnimMontage* AnimMontage, bool IsPrimary = true);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CastSpell(ACindyCharacter* StaffOwner, ESpellType SpellType, float ManaNeeded, float Cooldown);

	UFUNCTION(BlueprintPure)
	FTransform GetRelativeTransform(class USkeletalMeshComponent* SKMesh, class USpringArmComponent* CameraBoom);

	UFUNCTION(BlueprintPure)
	inline float CalculateManaRemaining(float ManaAmmount, float ManaNeeded) { return ManaAmmount - ManaNeeded; }
};