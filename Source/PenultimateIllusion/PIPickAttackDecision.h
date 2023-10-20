// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDecision.h"
/**
 * 
 */
class PENULTIMATEILLUSION_API PIPickAttackDecision : IDecision
{
public:
	PIPickAttackDecision();
	~PIPickAttackDecision();
	IDecision* MakeDecision(APIPBaseUnit* actingUnit, TArray<APIPBaseUnit*> allies, TArray<APIPBaseUnit*> enemies);
};
