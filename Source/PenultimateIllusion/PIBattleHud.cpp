// Fill out your copyright notice in the Description page of Project Settings.


#include "PIBattleHud.h"
#include "Blueprint/UserWidget.h"

void APIBattleHud::BeginPlay()
{
	Super::BeginPlay();
	UUserWidget* rootWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetHUDClass);

	rootWidget->SetOwningPlayer(GetOwningPlayerController());
	rootWidget->AddToPlayerScreen();

	RootWidget = rootWidget;
}
