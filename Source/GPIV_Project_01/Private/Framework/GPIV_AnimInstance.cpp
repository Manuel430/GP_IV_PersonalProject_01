// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GPIV_AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/GPIV_PlayerCharacter.h"

void UGPIV_AnimInstance::GetCrouch(bool crouching)
{
	bIsCrouching = crouching;
}

void UGPIV_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwnerCharacter = Cast <ACharacter>(TryGetPawnOwner());
	if (OwnerCharacter)
	{
		OwnerMovementComp = OwnerCharacter->GetCharacterMovement();
	}
}

void UGPIV_AnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (OwnerCharacter && OwnerMovementComp)
	{
		Speed = OwnerCharacter->GetVelocity().Length();
		bIsJumping = OwnerMovementComp->IsFalling();
	}
}

void UGPIV_AnimInstance::SetCrouch()
{
	bIsCrouching = OwnerMovementComp->IsCrouching();
}
