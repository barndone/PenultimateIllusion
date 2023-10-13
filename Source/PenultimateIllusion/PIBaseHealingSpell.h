// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PIBaseAction.h"
#include "PIBaseHealingSpell.generated.h"

USTRUCT()
struct FPIHealingSpellData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		bool AoE = false;

	UPROPERTY(EditAnywhere)
		float MagicMultiplier = 1.25f;
};

UCLASS()
class PENULTIMATEILLUSION_API UPIBaseHealingSpell : public UPIBaseAction
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		FText SpellName;

	UPROPERTY(EditAnywhere)
	FPIHealingSpellData SpellData;
};
