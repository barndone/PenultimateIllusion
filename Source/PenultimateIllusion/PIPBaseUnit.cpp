// Fill out your copyright notice in the Description page of Project Settings.


#include "PIPBaseUnit.h"

// Sets default values
APIPBaseUnit::APIPBaseUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APIPBaseUnit::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APIPBaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APIPBaseUnit::TakeDamage(const UPIBaseDamageSpell& _ability, APIPBaseUnit* _otherActor)
{
	int damageToTake = 0;

	//	if this is a physical ability/spell
	if (_ability.SpellData.Physical)
	{
		//	calculate using physical stats
		int baseDamage = (_otherActor->GetPhysicalAttack() / 2) - (PhysicalDefense / 2);
		if (baseDamage < 0) { baseDamage = 0; }
		float multipliedDamage = (float)baseDamage * _ability.SpellData.DamageMultiplier;
		damageToTake = (int)multipliedDamage;
	}
	//	otherwise, it is magical
	else
	{
		//	calculate using magical defense
		int baseDamage = (_otherActor->GetMagicalAttack() / 2) - (MagicalDefense / 2);
		if (baseDamage < 0) { baseDamage = 0; }
		float multipliedDamage = (float)baseDamage * _ability.SpellData.DamageMultiplier;
		damageToTake = (int)multipliedDamage;
	}

	CurrentHealth -= damageToTake;
}

void APIPBaseUnit::ApplyHealing(const UPIBaseHealingSpell& _ability, APIPBaseUnit* _otherActor)
{
	int healingToApply = 0;

	int baseHealing = _otherActor->GetMagicalAttack() / 2;
	float multipliedHealing = (float)baseHealing * _ability.SpellData.MagicMultiplier;
	healingToApply = (int)multipliedHealing;

	CurrentHealth += healingToApply;
	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

void APIPBaseUnit::GainCharge(float DeltaTime)
{
	//	TODO: implement global base charge speed
	int speedBreakpoints = Speed / 2;
	float chargeMultiplier = speedBreakpoints * 0.05f;

	if (AccumulatedTime >= chargeMultiplier * 1.5f)
	{
		if (!CanAct)
		{
			CanAct = true;

			//	TODO: Add this to the queue of units that can act
		}
	}
	else
	{
		//	TODO: check if the player is in a menu before incrementing time
		AccumulatedTime += DeltaTime;
	}
}

int APIPBaseUnit::GetPhysicalAttack()
{
	return PhysicalAttack;
}

int APIPBaseUnit::GetMagicalAttack()
{
	return MagicalAttack;
}

