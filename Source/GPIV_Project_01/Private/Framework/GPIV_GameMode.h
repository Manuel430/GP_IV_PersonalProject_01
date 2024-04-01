// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GPIV_GameMode.generated.h"

class UUSerWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRingsCountChanged, int32, RingsCount);

/**
 * 
 */
UCLASS()
class AGPIV_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<UUserWidget> GameHUDClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UGPIV_GameHUDWidget* GameHUD;

	UPROPERTY(VisibleAnywhere)
	int32 TotalRings = 0;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnRingsCountChanged OnRingsCountChanged;

	UFUNCTION(BlueprintCallable)
	void AddRing();

protected:
	virtual void BeginPlay() override;

};
