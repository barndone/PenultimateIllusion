// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PIDifficultyRatingDAG.h"
#include "PIGameInstance.generated.h"

/**
 * 
 */
UCLASS()
//	game instance- things that are available through the lifecycle of the application
//	things more user facing -> game instance
//	 things the (networkded) user shouldn't have acces to -> base gamemode
class PENULTIMATEILLUSION_API UPIGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	PIDifficultyRatingDAG* LevelMap;
	
	UFUNCTION()
		void GenerateMap();
};
