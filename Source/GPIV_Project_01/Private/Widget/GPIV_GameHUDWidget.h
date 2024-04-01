// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	//UFUNCTION(BlueprintCallable)
	//void InitializeHUD(AGPIV_GameMode* GameMode);

	//UFUNCTION(BlueprintCallable)
	//void SetRingsCount(int32 Count);
	
};
