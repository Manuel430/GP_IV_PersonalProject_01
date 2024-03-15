// Fill out your copyright notice in the Description page of Project Settings.


#include "GPIV_PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AGPIV_PlayerCharacter::AGPIV_PlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	ViewCamera = CreateDefaultSubobject<UCameraComponent>("View Camera");

	CameraBoom->SetupAttachment(GetRootComponent());
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

void AGPIV_PlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		InputSubsystem->ClearAllMappings();
		InputSubsystem->AddMappingContext(InputMapping, 0);
	}
}

void AGPIV_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComp)
	{
		EnhancedInputComp->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::Move);
		EnhancedInputComp->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::Jump);
		EnhancedInputComp->BindAction(SprintInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::Sprint);
		EnhancedInputComp->BindAction(WalkInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::Walk);
		EnhancedInputComp->BindAction(CrouchInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::Crouching);
		EnhancedInputComp->BindAction(StandInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::Standing);
	}
}

void AGPIV_PlayerCharacter::Move(const FInputActionValue& InputValue)
{
	FVector2D input = InputValue.Get<FVector2D>();
	input.Normalize();

	AddMovementInput(input.X * GetMoveRightDir());
}

void AGPIV_PlayerCharacter::Sprint(const FInputActionValue& InputValue)
{

	GetCharacterMovement()->MaxWalkSpeed *= SprintMultiplier;
}

void AGPIV_PlayerCharacter::Walk(const FInputActionValue& InputValue)
{

	GetCharacterMovement()->MaxWalkSpeed /= SprintMultiplier;
}

void AGPIV_PlayerCharacter::Crouching(const FInputActionValue& InputValue)
{
	if (GetCharacterMovement()->IsFalling())
	{
		return;
	}

	Crouch();
}

void AGPIV_PlayerCharacter::Standing(const FInputActionValue& InputValue)
{
	if (GetCharacterMovement()->IsFalling())
	{
		return;
	}

	UnCrouch();
}

FVector AGPIV_PlayerCharacter::GetMoveRightDir() const
{
	return ViewCamera->GetRightVector();
}
