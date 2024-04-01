// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GPIV_GameMode.h"

void AGPIV_GameMode::AddRing()
{
	TotalRings += 1;

	UE_LOG(LogTemp, Warning, TEXT("TOTAL RINGS: %d"), TotalRings);
}
