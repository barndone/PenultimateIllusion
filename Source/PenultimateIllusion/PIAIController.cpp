// Fill out your copyright notice in the Description page of Project Settings.


#include "PIAIController.h"

void APIAIController::BeginPlay()
{
	Super::BeginPlay();
}

void APIAIController::GenerateEnemyComp(const int& difficultyRating)
{
	//TODO: Implement difficulty rating logic~
}

void APIAIController::AssignActiveUnit(APIPBaseUnit* unit)
{
	if (Party.Contains(unit))
	{
		ActiveUnit = unit;
		//	TODO: Begin Decision Making Process
	}
	else
	{
		ActiveUnit = nullptr;
	}
}