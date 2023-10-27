// Fill out your copyright notice in the Description page of Project Settings.


#include "PIGameInstance.h"

void UPIGameInstance::GenerateMap()
{
	LevelMap = new PIDifficultyRatingDAG();
	LevelMap->GenerateGameMap();
}
