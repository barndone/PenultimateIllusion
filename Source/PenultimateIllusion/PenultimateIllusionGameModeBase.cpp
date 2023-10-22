// Copyright Epic Games, Inc. All Rights Reserved.


#include "PenultimateIllusionGameModeBase.h"
#include "PIBattleHud.h"
#include "PIPlayerController.h"

APenultimateIllusionGameModeBase::APenultimateIllusionGameModeBase()
{
	HUDClass = APIBattleHud::StaticClass();
	PlayerControllerClass = APIPlayerController::StaticClass();
	
}

void APenultimateIllusionGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//	TODO: set up number of enemies to spawn/types/etc

	enemyController = Cast<APIAIController>(GetWorld()->SpawnActor(BaseAIControllerAsset));
}

void APenultimateIllusionGameModeBase::AddReadyUnit(APIPBaseUnit* unit)
{
	ReadyUnits.AddUnique(unit);

	if (!WaitForAction)
	{
		WaitForAction = true;
	}
	//	check if this is the only element in the list
	if (ReadyUnits.Num() == 1)
	{
		ActingUnitSwap();
	}
}

//	FIFO REMOVAL
void APenultimateIllusionGameModeBase::RemoveUnitAfterAction(APIPBaseUnit* unit)
{
	//	check that size != 0
	if (ReadyUnits.Num() != 0)
	{
		//	remove first entry in list-
		ReadyUnits.RemoveAt(0, 1, true);

		//	check if the size of ready units to 0
		if (ReadyUnits.Num() == 0)
		{
			WaitForAction = false;
		}
		//	if it isn't, assign next unit to wait for action from
		else
		{
			ActingUnitSwap();
		}
	}
}

void APenultimateIllusionGameModeBase::ActingUnitSwap()
{
	ActingUnit = ReadyUnits[0];
	OnActingUnitChange.Broadcast(ActingUnit);
}

