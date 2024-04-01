// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GPIV_GameHUDWidget.h"
#include "Components/TextBlock.h"

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
