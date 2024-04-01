// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Framework/GPIV_GameMode.h"
#include "Blueprint/UserWidget.h"
#include "GPIV_GameHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class UGPIV_GameHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* RingCount;

public:
	UFUNCTION(BlueprintCallable)
	void InitializeHUD(AGPIV_GameMode* GameMode);

	UFUNCTION(BlueprintCallable)
	void SetRingsCount(const int32 Count);
	
};
