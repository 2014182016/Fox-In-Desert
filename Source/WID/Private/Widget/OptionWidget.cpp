// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/OptionWidget.h"
#include "Widget/OptionDetailWidget.h"
#include "../WID.h"
#include "Core/WIDGameUserSettings.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"

void UOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OptionWidgetSwitcher->SetActiveWidgetIndex(0);

	ApplyButton->OnClicked.AddDynamic(this, &UOptionWidget::OnClickApplyButton);
	SetToDefaultButton->OnClicked.AddDynamic(this, &UOptionWidget::OnClickSetToDefaultButton);
	ReturnButton->OnClicked.AddDynamic(this, &UOptionWidget::OnClickReturnButton);
	GameplayOptionButton->OnClicked.AddDynamic(this, &UOptionWidget::OnClickGameplayOptionButton);
	ControlOptionButton->OnClicked.AddDynamic(this, &UOptionWidget::OnClickControlOptionButton);
	GraphicOptionButton->OnClicked.AddDynamic(this, &UOptionWidget::OnClickGraphicOptionButton);
	SoundOptionButton->OnClicked.AddDynamic(this, &UOptionWidget::OnClickSoundOptionButton);

	WIDGameUserSettings = Cast<UWIDGameUserSettings>(GEngine->GetGameUserSettings());
	verifyf(WIDGameUserSettings != nullptr, TEXT("Does not exist Game User Settings"));
}

void UOptionWidget::OnClickApplyButton()
{
	WIDGameUserSettings->ApplyGameSettings(GetOwningPlayer());
	WIDGameUserSettings->ApplySettings(false); // Apply settings and save data to ini config
	UpdateOptionSettings();
}

void UOptionWidget::OnClickSetToDefaultButton()
{
	WIDGameUserSettings->SetToDefaults();
	UpdateOptionSettings();
}

void UOptionWidget::OnClickReturnButton()
{
	if (UWIDUserWidget* OwningUserWidget = GetTypedOuter<UWIDUserWidget>())
	{
		WID::FHudEventInfoList HudEventInfoList;
		HudEventInfoList.Emplace(0);

		// Active menu widget
		OwningUserWidget->UpdateHudEvent(EHudEvent::WidgetSwitcher, HudEventInfoList);
	}
}

void UOptionWidget::OnClickGameplayOptionButton()
{
	OptionWidgetSwitcher->SetActiveWidgetIndex(0);
}

void UOptionWidget::OnClickControlOptionButton()
{
	OptionWidgetSwitcher->SetActiveWidgetIndex(1);
}

void UOptionWidget::OnClickGraphicOptionButton()
{
	OptionWidgetSwitcher->SetActiveWidgetIndex(2);
}

void UOptionWidget::OnClickSoundOptionButton()
{
	OptionWidgetSwitcher->SetActiveWidgetIndex(3);
}

void UOptionWidget::UpdateOptionSettings()
{
	for (int32 i = 0; i < OptionWidgetSwitcher->GetChildrenCount(); ++i)
	{
		UOptionDetailWidget* ChildDetailWidget = Cast<UOptionDetailWidget>(OptionWidgetSwitcher->GetChildAt(i));
		if (ChildDetailWidget)
		{
			ChildDetailWidget->UpdateGameSettings();
		}
	}
}