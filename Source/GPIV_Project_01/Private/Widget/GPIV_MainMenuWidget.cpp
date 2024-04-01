// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GPIV_MainMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGPIV_MainMenuWidget::NativeConstruct()
{
	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UGPIV_MainMenuWidget::OnPlayClick);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UGPIV_MainMenuWidget::OnQuitClick);
	}
}

void UGPIV_MainMenuWidget::OnPlayClick()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("GameMap_01"));
	}
}

void UGPIV_MainMenuWidget::OnQuitClick()
{
	APlayerController* SpecificPlayer = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), SpecificPlayer, EQuitPreference::Quit, true);
}
