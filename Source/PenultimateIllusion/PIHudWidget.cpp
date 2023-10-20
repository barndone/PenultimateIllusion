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

	APenultimateIllusionGameModeBase* gameMode = Cast<APenultimateIllusionGameModeBase>(GetWorld()->GetAuthGameMode());
	//	if this case did not fail AKA is not null
	if (gameMode != nullptr)
	{
		gameMode->OnActingUnitChange.AddDynamic(this, &UPIHudWidget::HandleNewActingUnit);
	}

	APIPlayerController* controller = Cast<APIPlayerController>(GetWorld()->GetFirstPlayerController());
	if (controller != nullptr)
	{
		controller->OnPartyInit.AddDynamic(this, &UPIHudWidget::InitializePartyHud);
	}

	controller->OnPartyInit.Broadcast(controller->GetParty());
}

void UPIHudWidget::HandleNewActingUnit(APIPBaseUnit* unit)
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

	skill->OnClicked.AddDynamic(this, &UPIHudWidget::InitializeAvailableSkills);
}

void UPIHudWidget::InitializeAvailableSkills()
{
	for(int i = 0; i < InitializedButtons.Num(); i++)
	{
		ParentObject->RemoveChild(InitializedButtons[i]);
		InitializedButtons[i]->ConditionalBeginDestroy();
	}

	InitializedButtons.Empty();

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
