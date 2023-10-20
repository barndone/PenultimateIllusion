// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PIBaseAction.h"
#include "PIBaseDamageSpell.generated.h"

/**
 * 
 */
//	UCLASS(CollapseCategories)
//	class UPIDamageSpellData : public UObject
//	{
//	
//	};

USTRUCT()
struct FPIDamageSpellData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		bool AoE = false;

	UPROPERTY(EditAnywhere)
		bool Physical = true;

	UPROPERTY(EditAnywhere)
		float DamageMultiplier = 1.25f;

	UPROPERTY(EditAnywhere)
		int UnlockLevel = 1;
};

UCLASS(BlueprintType)
class PENULTIMATEILLUSION_API UPIBaseDamageSpell : public UPIBaseAction
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FPIDamageSpellData SpellData;
};
