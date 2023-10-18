// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PIBaseAction.h"
#include "PIBaseDamageSpell.h"
#include "PIBaseHealingSpell.h"
#include "PIPBaseUnit.generated.h"

UCLASS()
class PENULTIMATEILLUSION_API APIPBaseUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APIPBaseUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TakeDamage(const UPIBaseDamageSpell& _ability, APIPBaseUnit* _otherActor);
	void ApplyHealing(const UPIBaseHealingSpell& _ability, APIPBaseUnit* _otherActor);
	void GainCharge(float DeltaTime);
	int GetPhysicalAttack();
	int GetMagicalAttack();


private:
	//	the level of this unit
	int Level = 1;
	//	the max health of this unit
	int MaxHealth = 10;
	//	 the current health of this unit (Initialized to maxHealth in constructor)
	int CurrentHealth;
	//	the physical attack of this unit
	int PhysicalAttack = 5;
	//	 the physical defense of this unit
	int PhysicalDefense = 5;
	//	 the magical attack of this unit
	int MagicalAttack = 5;
	//	 the magical defense of this unit
	int MagicalDefense = 5;
	//	 the speed of this unit
	int Speed = 5;
	//	the experience this unit has accumulated
	int Experience = 0;
	//	the experience this unit is worth
	int ExperienceVal = 30;
	//	the fill of the charge meter (normalized 0-1)
	float ChargeMeterFill = 0.0f;
	float AccumulatedTime = 0.0f;

	bool CanAct = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions", meta = (AllowPrivateAccess = true))
	TArray<UPIBaseAction*> Actions;
};
