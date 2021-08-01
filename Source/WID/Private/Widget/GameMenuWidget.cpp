// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GameMenuWidget.h"
#include "Core/WIDPlayerController.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Active game menu widget
	MenuWidgetSwitcher->SetActiveWidgetIndex(0);

	ReturnToGameButton->OnClicked.AddDynamic(this, &UGameMenuWidget::OnClickReturnToGameButton);
	OptionButton->OnClicked.AddDynamic(this, &UGameMenuWidget::OnClickOptionButton);
	ExitButton->OnClicked.AddDynamic(this, &UGameMenuWidget::OnClickExitButton);
}

void UGameMenuWidget::UpdateHudEvent(const EHudEvent HudEvent, const WID::FHudEventInfoList& HudEventInfoList)
{
	Super::UpdateHudEvent(HudEvent, HudEventInfoList);

	switch (HudEvent)
	{
	case EHudEvent::WidgetSwitcher:
		if (WID::CheckEventInfo(HudEventInfoList, 0))
		{
			const int32 ActiveIndex = HudEventInfoList[0].GetValue<int32>();
			MenuWidgetSwitcher->SetActiveWidgetIndex(ActiveIndex);
		}
		break;
	}
}

void UGameMenuWidget::OnClickReturnToGameButton()
{
	AWIDPlayerController* WIDPlayerController = GetOwningPlayer<AWIDPlayerController>();
	if (IsValid(WIDPlayerController))
	{
		WIDPlayerController->ToggleGameMenu();
	}
}

void UGameMenuWidget::OnClickOptionButton()
{
	// Active option widget
	MenuWidgetSwitcher->SetActiveWidgetIndex(1);
}

void UGameMenuWidget::OnClickExitButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("/Game/WID/Maps/LoadingMap")), true, TEXT("NextLevel=/Game/WID/Maps/MainMenu"));
}
