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
///**
// * 
// */
UCLASS()
class AGPIV_PlayerCharacter : public AGPIV_CharacterBase
{
	GENERATED_BODY()

public:
	AGPIV_PlayerCharacter();

private:

	UPROPERTY(visibleAnywhere, Category = "View")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, Category = "View")
	UCameraComponent* ViewCamera;

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
	UInputAction* SlideInputAction;

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
	void Slide(const FInputActionValue& InputValue);

	FVector GetMoveRightDir() const;
	float SprintMultiplier = 2;
	bool bIsCrouching;

public:

	bool GetCrouch();

	/*			Wall Jump			*/

private:
	UPROPERTY(EditDefaultsOnly, Category = "Walljump")
	float WallJumpForce = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Walljump")
	float WallDetectionDistance = 50.f;
	
	bool bCanWallJump = false;

	void CheckWallCollision();

	/*			Sliding			*/
private:
	UPROPERTY(EditDefaultsOnly, Category = "Slide")
	float SlideSpeedMultiplier = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Slide")
	float SlideTime = 5.0f;

	bool bIsSliding = false;

	void StartSlide();

	void StopSlide();

	/*			Animation			*/
	UGPIV_AnimInstance* PlayerAnimation;
};
