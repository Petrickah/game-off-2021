// Fill out your copyright notice in the Description page of Project Settings.


#include "CindyAnimator.h"

void UCindyAnimator::GetVelocityAxis(ACindyCharacter* CindyCharacter, float& Forward, float& Right) {
	FVector velocity = CindyCharacter->GetVelocity();
	FRotator rotation = CindyCharacter->GetActorRotation();

	FVector orientation = rotation.UnrotateVector(velocity);
	Forward = orientation.X;
	Right = orientation.Y;
}
