// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GPIV_GameMode.h"

void AGPIV_GameMode::AddRings(int32 NumRings)
{
	TotalRings += NumRings;
}

void AGPIV_GameMode::AddRing()
{
	TotalRings += 1;
}
