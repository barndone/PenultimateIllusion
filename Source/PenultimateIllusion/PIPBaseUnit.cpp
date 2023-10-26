// Fill out your copyright notice in the Description page of Project Settings.


#include "PIPBaseUnit.h"
#include "PenultimateIllusionGameModeBase.h"

// Sets default values
APIPBaseUnit::APIPBaseUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;
}

// Called when the game starts or when spawned
void APIPBaseUnit::BeginPlay()
{
	Super::BeginPlay();

	gameMode = Cast<APenultimateIllusionGameModeBase>(GetWorld()->GetAuthGameMode());
	//	if this case did not fail AKA is not null
	if (gameMode != nullptr)
	{
		ChargeTime = gameMode->BaseChargeTime;
		CalculateChargeMultiplier();
	}
	//	otherwise do nothing

}

// Called every frame
void APIPBaseUnit::Tick(float DeltaTime)
{
	if (!IsDead())
	{
		Super::Tick(DeltaTime);
		GainCharge(DeltaTime);
	}
}

void APIPBaseUnit::NormalAttack()
{
	TakeAction(BasicAttack);
}

void APIPBaseUnit::TakeAction(UPIBaseAction* action)
{
	//	first cast to damage
	UPIBaseDamageSpell* attack = Cast<UPIBaseDamageSpell>(action);

	if (attack != nullptr)
	{
		//	do the attack
		Target->ApplyDamage(*attack, this);
	}
	else
	{
		UPIBaseHealingSpell* heal = Cast<UPIBaseHealingSpell>(action);
		if (heal != nullptr)
		{
			//do the heal
			Target->ApplyHealing(*heal, this);
		}
	}


	CanAct = false;
	AccumulatedTime = 0.0f;
	Target = nullptr;

	gameMode->RemoveUnitAfterAction(this);
}

void APIPBaseUnit::ApplyDamage(const UPIBaseDamageSpell& _ability, APIPBaseUnit* _otherActor)
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

	if (CurrentHealth <= 0)
	{
		OnUnitDeath.Broadcast();
		gameMode->RemoveUnitAfterDeath(this);
	}

	OnHealthUpdate.Broadcast(CurrentHealth, MaxHealth);
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

	OnHealthUpdate.Broadcast(CurrentHealth, MaxHealth);
}

void APIPBaseUnit::GainCharge(float DeltaTime)
{
	if (AccumulatedTime >= ChargeTime)
	{
		if (!CanAct)
		{
			OnChargeUpdate.Broadcast(ChargeTime / ChargeTime);
			CanAct = true;
			

			if (gameMode != nullptr)
			{
				gameMode->AddReadyUnit(this);
			}
		}
	}
	else
	{
		//	TODO: check if the player is in a menu before incrementing time
		AccumulatedTime += DeltaTime;

		OnChargeUpdate.Broadcast(AccumulatedTime / ChargeTime);
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

int APIPBaseUnit::GetPhysicalDefense()
{
	return PhysicalDefense;
}

int APIPBaseUnit::GetMagicalDefense()
{
	return MagicalDefense;
}

void APIPBaseUnit::CalculateChargeMultiplier()
{
	int speedBreakpoints = Speed / 2;
	float chargeMultiplier = speedBreakpoints * 0.05f;

	ChargeTime = ChargeTime - chargeMultiplier;
}

bool APIPBaseUnit::IsDead() const
{
	return CurrentHealth <= 0;
}

int APIPBaseUnit::GetCurrentHealth()
{
	return CurrentHealth;
}

int APIPBaseUnit::GetMaxHealth()
{
	return MaxHealth;
}

float APIPBaseUnit::GetChargeValue()
{
	return AccumulatedTime / ChargeTime;
}

bool APIPBaseUnit::CanHeal()
{
	return IsHealer;
}

float APIPBaseUnit::GetHealthPercent()
{
	return (float)(CurrentHealth / MaxHealth);
}
