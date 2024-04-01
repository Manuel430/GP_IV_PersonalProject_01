// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GPIV_GameHUDWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UGPIV_GameHUDWidget::NativeConstruct()
{
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UGPIV_GameHUDWidget::OnQuitClick);
	}

	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
}

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

void UGPIV_GameHUDWidget::OnQuitClick()
{
	APlayerController* SpecificPlayer = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), SpecificPlayer, EQuitPreference::Quit, true);
}
