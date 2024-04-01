// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GPIV_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class AGPIV_MainMenu : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	virtual void BeginPlay() override;
};
