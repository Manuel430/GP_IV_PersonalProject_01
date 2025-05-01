# 2.5D Sidescroller in Unreal
## About
For a personal project in my Game Programming IV class, I decided to work on a sidescroller platformer game in Unreal 5. The final turn in of the project was a simple fan game where the player has to collect all of the rings in their own time, having to crawl, jump, and run to get them all.

## Coding
### Player Movement
Using the Enhanced Input Component, it was simple as making sure each input was made and binded into the player character script, connecting them to different functions so they could perform all the tasks needed to play the game.
```cpp
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
```

While crouching and sprinting are simple, the Jumping input had an extra set of code because not only did the player need to jump, but they also needed to be determined if they are able to wall jump. If the player is capapble of wall jumping, then it will lead to a function that will launch the player off of the wall, allowing them to wall jump to get to a higher area.
```cpp
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
```

```cpp
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
```

Another interesting difficulty I had when trying to program the player movement was flipping the character, as with the game being 2.5d, it would be annoying to have to turn the player in an animation, so instead, the character mesh gets rotated, as if the whole player tries to rotate, the camera gets buggy and starts freaking out. So focusing on the mesh instead of the player, it allows the camera to remain in place as it follows the moving player.
```cpp
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
```

### Ring Collection
Ring collecting is the main aspect of the game, so making sure it work is the important part of this project. To start, the GameHUD Widget will be used to hold the amount of rings that are being collected, starting out as zero and then setting the dynamic to change the text widget to the count, which will be updating whenever the player collects a ring.
```h
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* RingCount;

	UFUNCTION(BlueprintCallable)
	void SetRingsCount(const int32 Count)
```

```cpp
void UGPIV_GameHUDWidget::InitializeHUD(AGPIV_GameMode* GameMode)
{
	if (GameMode)
	{
		RingCount->SetText(FText::AsNumber(0));

		GameMode->OnRingsCountChanged.AddDynamic(this, &UGPIV_GameHUDWidget::SetRingsCount);
	}
}

void UGPIV_GameHUDWidget::SetRingsCount(const int32 Count)
{
	RingCount->SetText(FText::AsNumber(Count));
}
```

As the rings spin around as an animation, when the player enters their area of the OnSphereOverlap, it will cast its own PlayerCharacter to the player and use their AddRing() Function, which calls to the GameMode to use their AddRing() function, adding one ring into its counter and brodcasting the OnRingsCountChange Delegate to the GameHUDWidgetm adding to the SetRingsCount() to add the updated count to the screen.
```cpp
void AGPIV_RingItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGPIV_PlayerCharacter* PlayerCharacter = Cast<AGPIV_PlayerCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		PlayerCharacter->AddRing();

		Destroy();

	}
}
```

```cpp
void AGPIV_PlayerCharacter::AddRing()
{
	GameMode->AddRing();
}
```

```cpp
void AGPIV_GameMode::AddRing()
{
	TotalRings += 1;

	OnRingsCountChanged.Broadcast(TotalRings);
}
```

```cpp
void UGPIV_GameHUDWidget::InitializeHUD(AGPIV_GameMode* GameMode)
{
	if (GameMode)
	{
		RingCount->SetText(FText::AsNumber(0));

		GameMode->OnRingsCountChanged.AddDynamic(this, &UGPIV_GameHUDWidget::SetRingsCount);
	}
}

void UGPIV_GameHUDWidget::SetRingsCount(const int32 Count)
{
	RingCount->SetText(FText::AsNumber(Count));
}
```
