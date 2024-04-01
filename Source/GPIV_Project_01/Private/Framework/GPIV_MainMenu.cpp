// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GPIV_MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AGPIV_MainMenu::BeginPlay()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	if (IsValid(MainMenuWidgetClass))
	{
		UUserWidget* Widget = CreateWidget(GetWorld(), MainMenuWidgetClass);

		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}
