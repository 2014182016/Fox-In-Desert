// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SoundOptionWidget.h"
#include "Components/Slider.h"
#include "Components/CheckBox.h"

void USoundOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MasterSoundSlider->OnValueChanged.AddDynamic(this, &USoundOptionWidget::OnValueChangedMasterSoundSlider);
	MasterSoundCheckBox->OnCheckStateChanged.AddDynamic(this, &USoundOptionWidget::OnCheckStateChangedMasterSoundCheckBox);
	BackgroundSoundSlider->OnValueChanged.AddDynamic(this, &USoundOptionWidget::OnValueChangedBackgroundSoundSlider);
	BackgroundSoundCheckBox->OnCheckStateChanged.AddDynamic(this, &USoundOptionWidget::OnCheckStateChangedBackgroundSoundCheckBox);
	EffectSoundSlider->OnValueChanged.AddDynamic(this, &USoundOptionWidget::OnValueChangedEffectSoundSlider);
	EffectSoundCheckBox->OnCheckStateChanged.AddDynamic(this, &USoundOptionWidget::OnCheckStateChangedEffectSoundCheckBox);
}

void USoundOptionWidget::UpdateGameSettings()
{
	MasterSoundSlider->SetValue(WIDGameUserSettings->MasterSoundVolume);
	MasterSoundCheckBox->SetCheckedState(WIDGameUserSettings->bMasterSoundEnabled ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	BackgroundSoundSlider->SetValue(WIDGameUserSettings->BackgroundSoundVolume);
	BackgroundSoundCheckBox->SetCheckedState(WIDGameUserSettings->bBackgroundSoundEnabled ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	EffectSoundSlider->SetValue(WIDGameUserSettings->EffectSoundVolume);
	EffectSoundCheckBox->SetCheckedState(WIDGameUserSettings->bEffectSoundEnabled ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
}

void USoundOptionWidget::OnValueChangedMasterSoundSlider(const float Value)
{
	WIDGameUserSettings->MasterSoundVolume = Value;
}

void USoundOptionWidget::OnCheckStateChangedMasterSoundCheckBox(const bool Value)
{
	WIDGameUserSettings->bMasterSoundEnabled = Value;
}

void USoundOptionWidget::OnValueChangedBackgroundSoundSlider(const float Value)
{
	WIDGameUserSettings->BackgroundSoundVolume = Value;
}

void USoundOptionWidget::OnCheckStateChangedBackgroundSoundCheckBox(const bool Value)
{
	WIDGameUserSettings->bBackgroundSoundEnabled = Value;
}

void USoundOptionWidget::OnValueChangedEffectSoundSlider(const float Value)
{
	WIDGameUserSettings->EffectSoundVolume = Value;
}

void USoundOptionWidget::OnCheckStateChangedEffectSoundCheckBox(const bool Value)
{
	WIDGameUserSettings->bEffectSoundEnabled = Value;
}