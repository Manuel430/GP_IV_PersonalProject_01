// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GPIV_AnimInstance.generated.h"

class ACharacter;
class UCharacterMovementComponent;
class AGPIV_PlayerCharacter;
/**
 * 
 */
UCLASS()
class UGPIV_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (BlueprintThreadSafe))
	float GetSpeed() const { return Speed; }

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (BlueprintThreadSafe))
	bool IsMoving() const { return Speed != 0; }

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (BlueprintThreadSafe))
	bool IsNotMoving() const { return Speed == 0; }

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (BlueprintThreadSafe))
	bool IsJumping() const { return bIsJumping; }

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (BlueprintThreadSafe))
	bool IsOnGround() const { return !bIsJumping; }

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (BlueprintThreadSafe))
	bool IsCrouching() const { return bIsCrouching; }

	void GetCrouch(bool crouching);

private:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	void SetCrouch();

	const ACharacter* OwnerCharacter;
	const UCharacterMovementComponent* OwnerMovementComp;

	float Speed;
	bool bIsJumping;
	bool bIsCrouching;
};
