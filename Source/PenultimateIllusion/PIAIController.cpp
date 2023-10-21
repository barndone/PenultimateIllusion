// Fill out your copyright notice in the Description page of Project Settings.


#include "PIAIController.h"

APIAIController::APIAIController()
{
	//	TODO: set up decision tree
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
		//	figure out how to clean up this memory correctly
		auto _ = Destroy(Decisions[i]);
	}

	Decisions.Empty();
}

void APIAIController::BeginPlay()
{
	Super::BeginPlay();


}

void APIAIController::GenerateEnemyComp(const int& difficultyRating)
{
	//TODO: Implement difficulty rating logic~
}

void APIAIController::AssignActiveUnit(APIPBaseUnit* unit)
{
	if (Party.Contains(unit))
	{
		ActiveUnit = unit;
		//	TODO: Begin Decision Making Process
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

	} while (currentDecision != nullptr);
}
