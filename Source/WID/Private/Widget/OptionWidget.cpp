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

	ApplyButton->OnClicked.AddDynamic(this, &UOptionWidget::OnClickApplyButton);
	ResetToDefaultButton->OnClicked.AddDynamic(this, &UOptionWidget::OnClickResetToDefaultButton);
	ReturnButton->OnClicked.AddDynamic(this, &UOptionWidget::OnClickReturnButton);
	GameplayOptionButton->OnClicked.AddDynamic(this, &UOptionWidget::OnClickGameplayOptionButton);
	ControlOptionButton->OnClicked.AddDynamic(this, &UOptionWidget::OnClickControlOptionButton);
	GraphicOptionButton->OnClicked.AddDynamic(this, &UOptionWidget::OnClickGraphicOptionButton);
	SoundOptionButton->OnClicked.AddDynamic(this, &UOptionWidget::OnClickSoundOptionButton);

	WIDGameUserSettings = Cast<UWIDGameUserSettings>(GEngine->GetGameUserSettings());
	verifyf(WIDGameUserSettings != nullptr, TEXT("Does not exist Game User Settings"));

	OptionWidgetSwitcher->SetActiveWidgetIndex(0);
	UpdateActiveOptionSetting();
}

void UOptionWidget::OnClickApplyButton()
{
	WIDGameUserSettings->ApplyGameSettings(GetOwningPlayer());
	WIDGameUserSettings->ApplySettings(false); // Apply settings and save data to ini config
	UpdateActiveOptionSetting();
}

void UOptionWidget::OnClickResetToDefaultButton()
{
	WIDGameUserSettings->SetToDefaults();
	UpdateActiveOptionSetting();
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
	OptionWidgetSwitcher->SetActiveWidgetIndex(3);
	UpdateActiveOptionSetting();
}

void UOptionWidget::OnClickControlOptionButton()
{
	OptionWidgetSwitcher->SetActiveWidgetIndex(1);
	UpdateActiveOptionSetting();
}

void UOptionWidget::OnClickGraphicOptionButton()
{
	OptionWidgetSwitcher->SetActiveWidgetIndex(0);
	UpdateActiveOptionSetting();
}

void UOptionWidget::OnClickSoundOptionButton()
{
	OptionWidgetSwitcher->SetActiveWidgetIndex(2);
	UpdateActiveOptionSetting();
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

void UOptionWidget::UpdateActiveOptionSetting()
{
	UOptionDetailWidget* ChildDetailWidget = Cast<UOptionDetailWidget>(OptionWidgetSwitcher->GetActiveWidget());
	if (ChildDetailWidget)
	{
		ChildDetailWidget->UpdateGameSettings();
	}
}