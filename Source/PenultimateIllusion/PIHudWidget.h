// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PIPBaseUnit.h"
#include "PIHudWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClickDelegate);
/**
 * 
 */
UCLASS()
class PENULTIMATEILLUSION_API UPIHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void HandleNewActingUnit(APIPBaseUnit* unit);
	UFUNCTION()
	void InitializeAvailableSkills();
	UPROPERTY()
	FClickDelegate click;
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true, BindWidget))
		class UScrollBox* ParentObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<class UButton*> InitializedButtons;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	APIPBaseUnit* currentUnit;
};