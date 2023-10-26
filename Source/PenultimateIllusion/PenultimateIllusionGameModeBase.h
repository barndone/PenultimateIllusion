// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PIPBaseUnit.h"
#include "PIAIController.h"
#include "PenultimateIllusionGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActingUnitChange, APIPBaseUnit*, unit);

UCLASS()
class PENULTIMATEILLUSION_API APenultimateIllusionGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float BaseChargeTime = 3.0f;
	UPROPERTY(EditAnywhere)
	TArray<APIPBaseUnit*> ReadyUnits;
	UPROPERTY()
	bool WaitForAction = false;
	UPROPERTY()
	APIPBaseUnit* ActingUnit;


	UPROPERTY(EditAnywhere)
	int EnemiesToSpawn;

	APenultimateIllusionGameModeBase();

	UFUNCTION()
	void AddReadyUnit(APIPBaseUnit* unit);
	UFUNCTION()
	void RemoveUnitAfterAction(APIPBaseUnit* unit);
	UFUNCTION()
		void RemoveUnitAfterDeath(APIPBaseUnit* unit);
	void ActingUnitSwap();

	UFUNCTION()
		void HandleDefeat();

	UFUNCTION()
		void HandleVictory();

	APIAIController* GetAIController();

	UPROPERTY(BlueprintAssignable)
	FOnActingUnitChange OnActingUnitChange;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UClass* BaseAIControllerAsset;

	UPROPERTY()
	APIAIController* enemyController;

	bool GameOver = false;
	bool Victory = false;


};
