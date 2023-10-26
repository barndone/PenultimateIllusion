// Fill out your copyright notice in the Description page of Project Settings.


#include "PIAIController.h"
#include "PIPlayerController.h"

APIAIController::APIAIController()
{
	PICanHealDecision* canHealDecision = new PICanHealDecision();
	PICheckHealthDecision* checkAllyHealthDecision = new PICheckHealthDecision();
	PIPickEnemyDecision* pickEnemyTargetDecision = new PIPickEnemyDecision();
	PIPickAttackDecision* pickAttackDecision = new PIPickAttackDecision();

	canHealDecision->TrueBranch = checkAllyHealthDecision;
	canHealDecision->FalseBranch = pickEnemyTargetDecision;

	//	TODO: implement pickHealDecision
	checkAllyHealthDecision->FalseBranch = pickEnemyTargetDecision;

	pickEnemyTargetDecision->TrueBranch = pickAttackDecision;

	//	can heal -> root
	RootDecision = canHealDecision;

	Decisions.Add(canHealDecision);
	Decisions.Add(checkAllyHealthDecision);
	Decisions.Add(pickEnemyTargetDecision);
	Decisions.Add(pickAttackDecision);
}

APIAIController::~APIAIController()
{
	for (int i = 0; i < Decisions.Num(); i++)
	{
		delete Decisions[i];
	}

	Decisions.Empty();
}

void APIAIController::BeginPlay()
{
	Super::BeginPlay();

	APenultimateIllusionGameModeBase* gameMode = Cast<APenultimateIllusionGameModeBase>(GetWorld()->GetAuthGameMode());
	//	if this case did not fail AKA is not null
	if (gameMode != nullptr)
	{
		gameMode->OnActingUnitChange.AddDynamic(this, &APIAIController::AssignActiveUnit);
	}

	APIPlayerController* playerController = Cast<APIPlayerController>(GetWorld()->GetFirstPlayerController());
	if (playerController != nullptr)
	{
		playerController->OnPartyInit.AddDynamic(this, &APIAIController::PopulatePlayerPartyRef);
	}

	GenerateEnemyComp(gameMode->EnemiesToSpawn);
}

TArray<APIPBaseUnit*> APIAIController::GetParty()
{
	return Party;
}

void APIAIController::GenerateEnemyComp(const int& difficultyRating)
{
	
	//	HACK: placeholder implementation
	//	TODO: integrate actual comp generation
	//	TODO: Implement difficulty rating logic~
	for (int i = 0; i < difficultyRating; ++i)
	{
		APIPBaseUnit* enemy = Cast<APIPBaseUnit>(GetWorld()->SpawnActor(PossibleEnemyBP[0]));
		if (enemy != nullptr)
		{
			Party.Add(enemy);
		}
	}

}

void APIAIController::AssignActiveUnit(APIPBaseUnit* unit)
{
	if (Party.Contains(unit))
	{
		ActiveUnit = unit;
		MakeDecision();
	}
	else
	{
		ActiveUnit = nullptr;
	}
}

void APIAIController::MakeDecision()
{
	IDecision* currentDecision = RootDecision;

	do
	{
		currentDecision = currentDecision->MakeDecision(ActiveUnit, Party, PlayerParty);
	} while (currentDecision != nullptr);

	ActiveUnit = nullptr;
}

void APIAIController::PopulatePlayerPartyRef(TArray<APIPBaseUnit*> playerP)
{
	PlayerParty = playerP;
}
