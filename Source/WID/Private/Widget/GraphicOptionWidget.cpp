// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GraphicOptionWidget.h"
#include "Widget/OptionButton.h"
#include "Components/Slider.h"
#include "Components/CheckBox.h"

void UGraphicOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	WindowModeOptionButton->OnIndexChanged.AddDynamic(this, &UGraphicOptionWidget::OnIndexChangedWindowModeOptionButton);
	ResolutionOptionButton->OnIndexChanged.AddDynamic(this, &UGraphicOptionWidget::OnIndexChangedResolutionOptionButton);
	BrightnessSlider->OnValueChanged.AddDynamic(this, &UGraphicOptionWidget::OnValueChangedMouseBrightnessSlider);
	VSyncCheckBox->OnCheckStateChanged.AddDynamic(this, &UGraphicOptionWidget::OnCheckStateChangedVSyncCheckBox);
	GraphicQualityOptionButton->OnIndexChanged.AddDynamic(this, &UGraphicOptionWidget::OnIndexChangedGraphicQualityOptionButton);
	AAOptionButton->OnIndexChanged.AddDynamic(this, &UGraphicOptionWidget::OnIndexChangedAAOptionButton);
	PPOptionButton->OnIndexChanged.AddDynamic(this, &UGraphicOptionWidget::OnIndexChangedPPOptionButton);
	ShadowQualityOptionButton->OnIndexChanged.AddDynamic(this, &UGraphicOptionWidget::OnIndexChangedShadowQualityOptionButton);
	TextureQualityOptionButton->OnIndexChanged.AddDynamic(this, &UGraphicOptionWidget::OnIndexChangedTextureQualityOptionButton);
	EffectQualityOptionButton->OnIndexChanged.AddDynamic(this, &UGraphicOptionWidget::OnIndexChangedEffectQualityOptionButton);
}

void UGraphicOptionWidget::UpdateGameSettings()
{
	WindowModeOptionButton->SetIndex(WIDGameUserSettings->WindowMode);
	ResolutionOptionButton->SetIndex(WIDGameUserSettings->ResolutionType);
	BrightnessSlider->SetValue(WIDGameUserSettings->GetBrightnessInRange());
	VSyncCheckBox->SetCheckedState(WIDGameUserSettings->bVSync ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	GraphicQualityOptionButton->SetIndex(WIDGameUserSettings->GraphicQuality);
	AAOptionButton->SetIndex(WIDGameUserSettings->AAQuality);
	PPOptionButton->SetIndex(WIDGameUserSettings->PPQuality);
	ShadowQualityOptionButton->SetIndex(WIDGameUserSettings->ShadowQuality);
	TextureQualityOptionButton->SetIndex(WIDGameUserSettings->TextureQuality);
	EffectQualityOptionButton->SetIndex(WIDGameUserSettings->EffectQuality);
}

void UGraphicOptionWidget::OnIndexChangedWindowModeOptionButton(const int32 Index)
{
	WIDGameUserSettings->WindowMode = Index;
}

void UGraphicOptionWidget::OnIndexChangedResolutionOptionButton(const int32 Index)
{
	WIDGameUserSettings->ResolutionType = WID::EResolution::ConvertIntToType(Index);
}

void UGraphicOptionWidget::OnValueChangedMouseBrightnessSlider(const float Value)
{
	WIDGameUserSettings->SetBrightnessInRange(Value);
}

void UGraphicOptionWidget::OnCheckStateChangedVSyncCheckBox(const bool Value)
{
	WIDGameUserSettings->bVSync = Value;
}

void UGraphicOptionWidget::OnIndexChangedGraphicQualityOptionButton(const int32 Index)
{
	// Applies to the rest of option settings only when the graphic option is changed
	if (WIDGameUserSettings->GraphicQuality != Index)
	{
		AAOptionButton->SetIndex(Index);
		PPOptionButton->SetIndex(Index);
		ShadowQualityOptionButton->SetIndex(Index);
		TextureQualityOptionButton->SetIndex(Index);
		EffectQualityOptionButton->SetIndex(Index);
	}

	WIDGameUserSettings->GraphicQuality = Index;
}

void UGraphicOptionWidget::OnIndexChangedAAOptionButton(const int32 Index)
{
	WIDGameUserSettings->AAQuality = Index;
}

void UGraphicOptionWidget::OnIndexChangedPPOptionButton(const int32 Index)
{
	WIDGameUserSettings->PPQuality = Index;
}

void UGraphicOptionWidget::OnIndexChangedShadowQualityOptionButton(const int32 Index)
{
	WIDGameUserSettings->ShadowQuality = Index;
}

void UGraphicOptionWidget::OnIndexChangedTextureQualityOptionButton(const int32 Index)
{
	WIDGameUserSettings->TextureQuality = Index;
}

void UGraphicOptionWidget::OnIndexChangedEffectQualityOptionButton(const int32 Index)
{
	WIDGameUserSettings->EffectQuality = Index;
}