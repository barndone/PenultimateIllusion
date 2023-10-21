// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PIPBaseUnit.h"

#include "CoreMinimal.h"
#include "IDecision.h"
#include "AIController.h"

#include "PICanHealDecision.h"
#include "PICheckHealthDecision.h"
#include "PIPickEnemyDecision.h"
#include "PIPickAttackDecision.h"


#include "PIAIController.generated.h"

/**
 * 
 */
UCLASS()
class PENULTIMATEILLUSION_API APIAIController : public AAIController
{
	GENERATED_BODY()

public:
	APIAIController();
	~APIAIController();
protected:
	virtual void BeginPlay() override;

public:
	//	the list of spawned enemies
	UPROPERTY(EditAnywhere)
	TArray<APIPBaseUnit*> Party;

private:
	//	list of possible enemies this controller can spawn per round
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<APIPBaseUnit*> PossibleEnemies;

	//	the currently active unit (if there is one)
	UPROPERTY(VisibleAnywhere)
	APIPBaseUnit* ActiveUnit;

	IDecision* RootDecision;

	TArray<IDecision*> Decisions;

	UFUNCTION()
	void GenerateEnemyComp(const int& difficultyRating);
	UFUNCTION()
	void AssignActiveUnit(APIPBaseUnit* unit);

	UFUNCTION()
		void MakeDecision();

};
