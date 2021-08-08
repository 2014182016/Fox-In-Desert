// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ControlOptionWidget.h"
#include "Components/Slider.h"
#include "Components/CheckBox.h"

void UControlOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MouseSensitivitySlider->OnValueChanged.AddDynamic(this, &UControlOptionWidget::OnValueChangedMouseSensitivitySlider);
	InvertMouseXAxisCheckBox->OnCheckStateChanged.AddDynamic(this, &UControlOptionWidget::OnCheckStateChangedInvertMouseXAxisCheckBox);
	InvertMouseYAxisCheckBox->OnCheckStateChanged.AddDynamic(this, &UControlOptionWidget::OnCheckStateChangedInvertMouseYAxisCheckBox);
	ToggleSprintCheckBox->OnCheckStateChanged.AddDynamic(this, &UControlOptionWidget::OnCheckStateChangedToggleSprintCheckBox);
}

void UControlOptionWidget::UpdateGameSettings()
{
	MouseSensitivitySlider->SetValue(WIDGameUserSettings->GetMouseSensitivityInRange());
	InvertMouseXAxisCheckBox->SetCheckedState(WIDGameUserSettings->bInvertMouseXAxis ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	InvertMouseYAxisCheckBox->SetCheckedState(WIDGameUserSettings->bInvertMouseYAxis ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	ToggleSprintCheckBox->SetCheckedState(WIDGameUserSettings->bToggleSprint ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
}

void UControlOptionWidget::OnValueChangedMouseSensitivitySlider(const float Value)
{
	WIDGameUserSettings->SetMouseSensitivityInRange(Value);
}

void UControlOptionWidget::OnCheckStateChangedInvertMouseXAxisCheckBox(const bool Value)
{
	WIDGameUserSettings->bInvertMouseXAxis = Value;
}

void UControlOptionWidget::OnCheckStateChangedInvertMouseYAxisCheckBox(const bool Value)
{
	WIDGameUserSettings->bInvertMouseYAxis = Value;
}

void UControlOptionWidget::OnCheckStateChangedToggleSprintCheckBox(const bool Value)
{
	WIDGameUserSettings->bToggleSprint = Value;
}
