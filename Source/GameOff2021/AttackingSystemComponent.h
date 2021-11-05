// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackingSystemComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEOFF2021_API UAttackingSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackingSystemComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class ACindyCharacter* CindyCharacter;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float AttackDuration = 0.2f;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	bool StaffEquiped, Attacking;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquipStaff, bool, HasStaff);
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FEquipStaff EquipStaff;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquippingStaff);
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FEquippingStaff EquippingStaff;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttack, bool, ReadyToAttack);
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FAttack PrimaryAttack;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FAttack SecondaryAttack;

	UFUNCTION(BlueprintCallable)
	void OnEquipStaff();

	UFUNCTION(BlueprintCallable)
	void OnAttack(bool IsPrimary);

	UFUNCTION(BlueprintCallable)
	void ToggleEquippedStaff(class USkeletalMeshComponent* Staff);

	UFUNCTION(BlueprintPure)
	inline float GetAttackDuration() { return AttackDuration; }
};
