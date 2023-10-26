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
	check(gameMode!= nullptr && "GameMode null on PlayerController.... wtf?")
	gameMode->OnActingUnitChange.AddDynamic(this, &APIPlayerController::AssignActiveUnit);

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
		check(unit != nullptr && "Somehow instantiated null party member...")
		Party.Add(unit);
		unit->OnUnitDeath.AddDynamic(this, &APIPlayerController::HandlePartyMemberDeath);
		
	}

	OnPartyInit.Broadcast(Party);
}

TArray<APIPBaseUnit*> APIPlayerController::GetParty()
{
	return Party;
}

bool APIPlayerController::ContainsUnit(APIPBaseUnit* unit)
{
	return Party.Contains(unit);
}

void APIPlayerController::HandlePartyMemberDeath()
{
	++DeadUnitCount;
	if (DeadUnitCount >= Party.Num())
	{
		OnDefeat.Broadcast();
	}
}
