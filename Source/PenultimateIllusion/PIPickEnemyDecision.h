// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDecision.h"

/**
 * 
 */
class PENULTIMATEILLUSION_API PIPickEnemyDecision : public IDecision
{
public:
	PIPickEnemyDecision();
	~PIPickEnemyDecision();

	UPROPERTY(EditAnywhere)
		IDecision* TrueBranch;
	UPROPERTY(EditAnywhere)
		IDecision* FalseBranch;

	IDecision* MakeDecision(APIPBaseUnit* actingUnit, TArray<APIPBaseUnit*>& allies, TArray<APIPBaseUnit*>& enemies) override;

};
