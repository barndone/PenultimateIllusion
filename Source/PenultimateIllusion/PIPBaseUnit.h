// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PIBaseAction.h"
#include "PIBaseDamageSpell.h"
#include "PIBaseHealingSpell.h"
#include "PIPBaseUnit.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChargeUpdate, const float&, fillAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthUpdate, const int&, curHealth, const int&,  maxHealth);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions")
		TArray<UPIBaseAction*> Actions;

	UPROPERTY()
		APIPBaseUnit* Target;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ApplyDamage(const UPIBaseDamageSpell& _ability, APIPBaseUnit* _otherActor);
	void ApplyHealing(const UPIBaseHealingSpell& _ability, APIPBaseUnit* _otherActor);
	UFUNCTION()
	void GainCharge(float DeltaTime);
	UFUNCTION()
	int GetPhysicalAttack();
	UFUNCTION()
	int GetMagicalAttack();

	UFUNCTION()
		int GetPhysicalDefense();
	UFUNCTION()
		int GetMagicalDefense();

	UFUNCTION()
	int GetCurrentHealth();
	UFUNCTION()
	int GetMaxHealth();
	UFUNCTION()
	float GetChargeValue();
	UFUNCTION()
		bool CanHeal();
	UFUNCTION()
		float GetHealthPercent();
	UFUNCTION()
		void TakeAction(UPIBaseAction* action);

	FOnHealthUpdate OnHealthUpdate;
	FOnChargeUpdate OnChargeUpdate;

private:
	//	the level of this unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	int Level = 1;
	//	the max health of this unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	int MaxHealth = 10;
	//	 the current health of this unit (Initialized to maxHealth in constructor)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	int CurrentHealth;
	//	the physical attack of this unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	int PhysicalAttack = 5;
	//	 the physical defense of this unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	int PhysicalDefense = 5;
	//	 the magical attack of this unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	int MagicalAttack = 5;
	//	 the magical defense of this unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	int MagicalDefense = 5;
	//	 the speed of this unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	int Speed = 5;
	//	the experience this unit has accumulated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	int Experience = 0;
	//	the experience this unit is worth
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	int ExperienceVal = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	float AccumulatedTime = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	float ChargeTime = 0.0f;
	bool CanAct = false;
	bool IsHealer = false;

	UPROPERTY()
	class APenultimateIllusionGameModeBase* gameMode;

	void CalculateChargeMultiplier();
	bool IsDead();
};
