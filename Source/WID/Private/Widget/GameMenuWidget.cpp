// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GameMenuWidget.h"
#include "Core/WIDPlayerController.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "../WID.h"

void UGameMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnNativeVisibilityChanged.AddUObject(this, &UGameMenuWidget::OnVisibilityChanged);

	// Active game menu widget
	MenuWidgetSwitcher->SetActiveWidgetIndex(0);

	ReturnToGameButton->OnClicked.AddDynamic(this, &UGameMenuWidget::OnClickReturnToGameButton);
	OptionButton->OnClicked.AddDynamic(this, &UGameMenuWidget::OnClickOptionButton);
	ExitButton->OnClicked.AddDynamic(this, &UGameMenuWidget::OnClickExitButton);
}

FReply UGameMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey().IsValid() && InKeyEvent.GetKey() == EKeys::Escape)
	{
		// GameMenuWidget Activated
		if (MenuWidgetSwitcher->GetActiveWidgetIndex() == 0)
		{
			AWIDPlayerController* WIDPlayerController = GetOwningPlayer<AWIDPlayerController>();
			if (IsValid(WIDPlayerController))
			{
				// If input is allowed, then ESC key is entered to perfrom ToggleGameMenu
				WIDPlayerController->SetSimpleInputMode(EInputMode::GameOnly);
			}
		}
		// OptionWidget Activated
		else if (MenuWidgetSwitcher->GetActiveWidgetIndex() == 1)
		{
			MenuWidgetSwitcher->SetActiveWidgetIndex(0);
		}
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
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
	MenuWidgetSwitcher->GetActiveWidget()->SetFocus();
}

void UGameMenuWidget::OnClickExitButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("/Game/WID/Maps/LoadingMap")), true, TEXT("NextLevel=/Game/WID/Maps/MainMenu"));
}

void UGameMenuWidget::OnVisibilityChanged(ESlateVisibility ChangedVisibility)
{
	if (IsVisible())
	{
		SetFocus();
	}
}