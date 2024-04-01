// Fill out your copyright notice in the Description page of Project Settings.


#include "GPIV_PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Framework/GPIV_AnimInstance.h"
#include "Framework/GPIV_GameMode.h"
#include "Kismet/GameplayStatics.h"

AGPIV_PlayerCharacter::AGPIV_PlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	ViewCamera = CreateDefaultSubobject<UCameraComponent>("View Camera");

	CameraBoom->SetupAttachment(GetRootComponent());
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

void AGPIV_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<AGPIV_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	check(GameMode);
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
		EnhancedInputComp->BindAction(TurnRightInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::TurnRight);
		EnhancedInputComp->BindAction(TurnLeftInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::TurnLeft);
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
	Crouch();
}

void AGPIV_PlayerCharacter::Standing(const FInputActionValue& InputValue)
{
	if (GetCharacterMovement()->IsFalling())
	{
		return;
	}

	bIsCrouching = false;
	UnCrouch();
}

void AGPIV_PlayerCharacter::TurnRight(const FInputActionValue& InputValue)
{
	FRotator NewRotator = FRotator::ZeroRotator;
	NewRotator.Yaw = 90;

	if (GetMesh())
	{
		GetMesh()->SetWorldRotation(NewRotator);
	}
}

void AGPIV_PlayerCharacter::TurnLeft(const FInputActionValue& InputValue)
{
	FRotator NewRotator = FRotator::ZeroRotator;
	NewRotator.Yaw = -90;

	if (GetMesh())
	{
		GetMesh()->SetWorldRotation(NewRotator);
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
	FVector Start = GetMesh()->GetComponentLocation();
	FVector End = Start + GetMesh()->GetForwardVector() * WallDetectionDistance;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	//DrawDebugLine(GetWorld(), Start, End, FColor::Emerald, true);

	bool bHit = GetWorld()->LineTraceMultiByChannel(HitResults, Start, End, ECC_WorldStatic, CollisionParams);
	float Distance = TNumericLimits<float>::Max();

	for (const FHitResult& result : HitResults)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s"), *result.GetActor()->GetName());

		if (result.GetActor() != this)
		{
			if (result.Distance < Distance)
			{
				Distance = result.Distance;
			}
		}
	}

	if (bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Distance to wall: %f"), Distance);
	}

	if (bHit && Distance <= WallDetectionDistance)
	{
		bCanWallJump = true;
	}
	else
	{
		bCanWallJump = false;
	}
}

void AGPIV_PlayerCharacter::AddRing()
{
	GameMode->AddRing();
}
