// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GPIV_CharacterBase.h"
#include "GPIV_PlayerCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
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

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& InputValue);

	FVector GetMoveRightDir() const;
};
