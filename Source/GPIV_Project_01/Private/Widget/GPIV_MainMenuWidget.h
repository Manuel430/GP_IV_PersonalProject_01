// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GPIV_MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class UGPIV_MainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* PlayButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* QuitButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnPlayClick();
	UFUNCTION()
		void OnQuitClick();
};
