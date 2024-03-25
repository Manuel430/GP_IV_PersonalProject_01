// Fill out your copyright notice in the Description page of Project Settings.


#include "GPIV_PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Framework/GPIV_AnimInstance.h"

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
		EnhancedInputComp->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::Jumping);
		EnhancedInputComp->BindAction(SprintInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::Sprint);
		EnhancedInputComp->BindAction(WalkInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::Walk);
		EnhancedInputComp->BindAction(CrouchInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::Crouching);
		EnhancedInputComp->BindAction(StandInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::Standing);
		EnhancedInputComp->BindAction(SlideInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::Slide);
	}
}

void AGPIV_PlayerCharacter::Move(const FInputActionValue& InputValue)
{
	FVector2D input = InputValue.Get<FVector2D>();
	input.Normalize();

	AddMovementInput(input.X * GetMoveRightDir());
}

void AGPIV_PlayerCharacter::Jumping(const FInputActionValue& InputValue)
{
	if (bCanWallJump)
	{
		FVector JumpDirection = GetActorUpVector() + GetActorForwardVector();
		JumpDirection.Normalize();

		LaunchCharacter(JumpDirection * WallJumpForce, false, true);
		bCanWallJump = false;
	}
	else
	{
		Jump();
	}

	CheckWallCollision();
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

	bIsCrouching = true;
	//PlayerAnimation->GetCrouch(bIsCrouching);
	Crouch();
}

void AGPIV_PlayerCharacter::Standing(const FInputActionValue& InputValue)
{
	if (GetCharacterMovement()->IsFalling())
	{
		return;
	}

	bIsCrouching = false;
	//PlayerAnimation->GetCrouch(bIsCrouching);
	UnCrouch();
}

void AGPIV_PlayerCharacter::Slide(const FInputActionValue& InputValue)
{
	if (!bIsCrouching)
	{
		return;
	}
	
	if (!bIsSliding && bIsCrouching)
	{
		StartSlide();
	}
}

FVector AGPIV_PlayerCharacter::GetMoveRightDir() const
{
	return ViewCamera->GetRightVector();
}

bool AGPIV_PlayerCharacter::GetCrouch()
{
	return bIsCrouching;
}

void AGPIV_PlayerCharacter::CheckWallCollision()
{
	FVector Start = GetActorLocation() + GetActorForwardVector();
	FVector End = Start + GetActorForwardVector() * WallDetectionDistance;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, CollisionParams);

	if (bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Distance to wall: %f"), HitResult.Distance);
	}

	if (bHit && HitResult.Distance <= WallDetectionDistance)
	{
		bCanWallJump = true;
	}
	else
	{
		bCanWallJump = false;
	}
}

void AGPIV_PlayerCharacter::StartSlide()
{
	if (!bIsSliding)
	{
		bIsSliding = true;

		GetCharacterMovement()->MaxWalkSpeedCrouched *= SlideSpeedMultiplier;
	}

	while (bIsSliding)
	{
		Crouch();
		
		SlideTime -= 1.0f;

		if (SlideTime <= 0)
		{
			StopSlide();
		}
	}
}

void AGPIV_PlayerCharacter::StopSlide()
{
	if (bIsSliding)
	{
		bIsSliding = false;

		GetCharacterMovement()->MaxWalkSpeedCrouched /= SlideSpeedMultiplier;

		SlideTime = 5.0f;
	}
}
