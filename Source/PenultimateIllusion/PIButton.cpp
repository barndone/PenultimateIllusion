// Fill out your copyright notice in the Description page of Project Settings.


#include "PIButton.h"

APIPBaseUnit* UPIButton::GetTarget()
{
	return target;
}

UPIBaseAction* UPIButton::GetAction()
{
	return action;
}

void UPIButton::HandleClick()
{
	OnPiClicked.Broadcast(this);
}

