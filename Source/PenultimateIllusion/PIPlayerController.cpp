// Fill out your copyright notice in the Description page of Project Settings.


#include "PIPlayerController.h"

APIPlayerController::APIPlayerController()
{
	
}

void APIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	gameMode = Cast<APenultimateIllusionGameModeBase>(GetWorld()->GetAuthGameMode());
	//	if this case did not fail AKA is not null
	if (gameMode != nullptr)
	{
		gameMode->OnActingUnitChange.AddDynamic(this, &APIPlayerController::AssignActiveUnit);
	}

	InitializeParty();
}

void APIPlayerController::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void APIPlayerController::AssignActiveUnit(APIPBaseUnit* unit)
{
	if (Party.Contains(unit))
	{
		ActiveUnit = unit;
	}
	else
	{
		ActiveUnit = nullptr;
	}
}

void APIPlayerController::InitializeParty()
{
	Party.Empty();

	for (int i = 0; i < MaxPartyCount; i++)
	{
		APIPBaseUnit* unit = Cast<APIPBaseUnit>(GetWorld()->SpawnActor(BaseUnitBPAsset));
		if (unit != nullptr)
		{
			Party.Add(unit);
		}
	}

	OnPartyInit.Broadcast(Party);
}

TArray<APIPBaseUnit*> APIPlayerController::GetParty()
{
	return Party;
}
