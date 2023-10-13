// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PENULTIMATEILLUSION_API APIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	//	set good defaults
	APIPlayerController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float _deltaTime) override;
	

private:
	//	TODO: include list of units
};
