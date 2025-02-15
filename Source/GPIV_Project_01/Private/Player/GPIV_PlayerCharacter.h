// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GPIV_CharacterBase.h"
#include "GPIV_PlayerCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UGPIV_AnimInstance;
class USkeletalMeshComponent;
///**
// * 
// */
UCLASS()
class AGPIV_PlayerCharacter : public AGPIV_CharacterBase
{
	GENERATED_BODY()

public:
	AGPIV_PlayerCharacter();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(visibleAnywhere, Category = "View")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, Category = "View")
	UCameraComponent* ViewCamera;

	UPROPERTY(EditDefaultsOnly, Category = "Rotate")
	USkeletalMeshComponent* PlayerBody;

	UPROPERTY(EditDefaultsOnly, Category = "GameMode")
	class AGPIV_GameMode* GameMode;

	virtual void PawnClientRestart() override;

	/*			Input			*/

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* SprintInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* WalkInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* CrouchInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* StandInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* TurnRightInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* TurnLeftInputAction;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& InputValue);

	UFUNCTION()
	void Jumping(const FInputActionValue& InputValue);
	
	UFUNCTION()
	void Sprint(const FInputActionValue& InputValue);
	
	UFUNCTION()
	void Walk(const FInputActionValue& InputValue);
	
	UFUNCTION()
	void Crouching(const FInputActionValue& InputValue);

	UFUNCTION()
	void Standing(const FInputActionValue& InputValue);

	UFUNCTION()
	void TurnRight(const FInputActionValue& InputValue);

	UFUNCTION()
	void TurnLeft(const FInputActionValue& InputValue);

	FVector GetMoveRightDir() const;
	float SprintMultiplier = 2;

public:

	bool bIsCrouching;

	bool GetCrouch();

	/*			Wall Jump			*/

private:
	UPROPERTY(EditDefaultsOnly, Category = "Walljump")
	float WallJumpForce = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Walljump")
	float WallDetectionDistance = 50.f;
	
	bool bCanWallJump = false;

	void CheckWallCollision();

	/*			Animation			*/
	UGPIV_AnimInstance* PlayerAnimation;

	/*			Coins			*/
public:
	UFUNCTION()
	void AddRing();
};
