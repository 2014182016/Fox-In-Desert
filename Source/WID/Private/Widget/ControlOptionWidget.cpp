// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ControlOptionWidget.h"
#include "Components/Slider.h"

void UControlOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MouseSensitivitySlider->OnValueChanged.AddDynamic(this, &UControlOptionWidget::OnValueChangedMouseSensitivitySlider);
}

void UControlOptionWidget::UpdateGameSettings()
{

}

void UControlOptionWidget::OnValueChangedMouseSensitivitySlider(const float Value)
{
	WIDGameUserSettings->SetMouseSensitivity(Value);
}
