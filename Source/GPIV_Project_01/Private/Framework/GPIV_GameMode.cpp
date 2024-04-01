// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GPIV_GameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/GPIV_GameHUDWidget.h"

void AGPIV_GameMode::AddRing()
{
	TotalRings += 1;

	UE_LOG(LogTemp, Warning, TEXT("TOTAL RINGS: %d"), TotalRings);
}

void AGPIV_GameMode::BeginPlay()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;

	GameHUD = Cast<UGPIV_GameHUDWidget>(CreateWidget(GetWorld(), GameHUDClass));
	check(GameHUD);

	GameHUD->AddToViewport();
}
