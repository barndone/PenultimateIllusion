// Fill out your copyright notice in the Description page of Project Settings.


#include "PIHudWidget.h"
#include "PenultimateIllusionGameModeBase.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "PIPartyMemberElement.h"
#include "PIPlayerController.h"
#include "Components/VerticalBox.h"

void UPIHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gameMode = Cast<APenultimateIllusionGameModeBase>(GetWorld()->GetAuthGameMode());
	//	if this case did not fail AKA is not null
	if (gameMode != nullptr)
	{
		gameMode->OnActingUnitChange.AddDynamic(this, &UPIHudWidget::HandleNewActingUnit);
	}

	controller = Cast<APIPlayerController>(GetWorld()->GetFirstPlayerController());
	if (controller != nullptr)
	{
		controller->OnPartyInit.AddDynamic(this, &UPIHudWidget::InitializePartyHud);
	}

	aiController = Cast<APIAIController>(gameMode->GetAIController());
	if (aiController != nullptr)
	{

	}

	controller->OnPartyInit.Broadcast(controller->GetParty());
}

void UPIHudWidget::CleanUpButtons()
{
	for (int i = 0; i < InitializedButtons.Num(); ++i)
	{
		ParentObject->RemoveChild(InitializedButtons[i]);
		InitializedButtons[i]->ConditionalBeginDestroy();
	}

	InitializedButtons.Empty();
}

UPIBaseAction* UPIHudWidget::GetPairedAction(int index) const
{
	return currentUnit->Actions[index];
}

void UPIHudWidget::GetBasicAttackTargets()
{
	InitializeTargetingButtons(currentUnit->BasicAttack);
}

void UPIHudWidget::HandleNewActingUnit(APIPBaseUnit* unit)
{
	CleanUpButtons();

	if (controller->ContainsUnit(unit))
	{
		currentUnit = unit;
		UButton* attack = NewObject<UButton>(UButton::StaticClass(), TEXT("attack"));
		UTextBlock* attackTitle = NewObject<UTextBlock>(UTextBlock::StaticClass(), TEXT("Title"));
		attackTitle->SetText(FText::FromString("Attack"));
		attack->AddChild(attackTitle);
		ParentObject->AddChild(attack);
		InitializedButtons.Add(attack);

		UButton* skill = NewObject<UButton>(UButton::StaticClass(), TEXT("skill"));
		UTextBlock* skillTitle = NewObject<UTextBlock>(UTextBlock::StaticClass(), TEXT("Title"));
		skillTitle->SetText(FText::FromString("Skills"));
		skill->AddChild(skillTitle);
		ParentObject->AddChild(skill);
		InitializedButtons.Add(skill);

		//	TODO: bind attack OnClick to show available targets-- show estimated damage
		attack->OnClicked.AddDynamic(this, &UPIHudWidget::GetBasicAttackTargets);
		//	TODO: check if unit is taunted, if so, skip to just attacking the target
		//	TODO: bind attack OnClick to unit's auto attack
		skill->OnClicked.AddDynamic(this, &UPIHudWidget::InitializeAvailableSkills);
	}
}

void UPIHudWidget::InitializeAvailableSkills()
{
	CleanUpButtons();

	for (int i = 0; i < currentUnit->Actions.Num(); i++)
	{
		UButton* button = NewObject<UButton>(UButton::StaticClass(), TEXT("Button"));
		UTextBlock* title = NewObject<UTextBlock>(UTextBlock::StaticClass(), TEXT("Title"));
		ParentObject->AddChild(button);
		title->SetText(currentUnit->Actions[i]->SpellName);
		button->AddChild(title);
		InitializedButtons.Add(button);
	}
}

void UPIHudWidget::InitializePartyHud(TArray<APIPBaseUnit*> partyToInit)
{
	for (int i = 0; i < partyToInit.Num(); i++)
	{
		UPIPartyMemberElement* partyBar = Cast<UPIPartyMemberElement>(CreateWidget<UUserWidget>(GetWorld(), PartyStatWidget));
		if (partyBar != nullptr)
		{
			PartyStatsHud->AddChild(partyBar);
			partyBar->PairNewUnit(partyToInit[i]);
		}
	}
}

void UPIHudWidget::InitializeTargetingButtons(const UPIBaseAction* action)
{
	//	TODO: implement button spawning for targeting each enemy
	CleanUpButtons();

	//	branch 1: target enemies
	if (action->TargetEnemies)
	{
		for (int i = 0; i < gameMode->GetAIController()->Party.Num(); ++i)
		{
			UButton* button = NewObject<UButton>(UButton::StaticClass(), TEXT("Button"));
			UTextBlock* title = NewObject<UTextBlock>(UTextBlock::StaticClass(), TEXT("Title"));
			ParentObject->AddChild(button);

			title->SetText(FText::FromString(gameMode->GetAIController()->Party[i]->GetName()));
			button->AddChild(title);
			InitializedButtons.Add(button);
		}
	}
	//	branch 2: target allies
	else 
	{
		for (int i = 0; i < controller->GetParty().Num(); ++i)
		{
			UButton* button = NewObject<UButton>(UButton::StaticClass(), TEXT("Button"));
			UTextBlock* title = NewObject<UTextBlock>(UTextBlock::StaticClass(), TEXT("Title"));
			ParentObject->AddChild(button);
		
			title->SetText(FText::FromString(controller->GetParty()[i]->GetName()));
			button->AddChild(title);
			InitializedButtons.Add(button);
		}
	}
}

FText UPIHudWidget::PassActionToUnit()
{
	return FText();
}
