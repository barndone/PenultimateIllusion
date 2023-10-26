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
	check(enemyController != nullptr && "EnemyController was null in GameMode, wtf?")
	enemyController->OnVictory.AddDynamic(this, &APenultimateIllusionGameModeBase::HandleVictory);
	auto* PC = Cast<APIPlayerController>(GetWorld()->GetFirstPlayerController());
	check(PC != nullptr && "PlayerController was null in GameMode, wtf?");
	PC->OnDefeat.AddDynamic(this, &APenultimateIllusionGameModeBase::HandleDefeat);

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

void APenultimateIllusionGameModeBase::RemoveUnitAfterDeath(APIPBaseUnit* unit)
{
	if (ReadyUnits.Num() != 0)
	{
		ReadyUnits.Remove(unit);

		if (ReadyUnits.Num() != 0)
		{
			if (ActingUnit == unit)
			{
				ActingUnitSwap();
			}
		}
	}
}

void APenultimateIllusionGameModeBase::ActingUnitSwap()
{
	ActingUnit = ReadyUnits[0];
	OnActingUnitChange.Broadcast(ActingUnit);
}

void APenultimateIllusionGameModeBase::HandleDefeat()
{
	GameOver = true;

	//	TODO: implement feedback
}

void APenultimateIllusionGameModeBase::HandleVictory()
{
	GameOver = true;
	Victory = true;

	//	TODO: implement feedback
}

bool APenultimateIllusionGameModeBase::IsGameOver() const
{
	return GameOver;
}

APIAIController* APenultimateIllusionGameModeBase::GetAIController()
{
	return enemyController;
}

