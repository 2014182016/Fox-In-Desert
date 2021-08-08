// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GameplayOptionWidget.h"
#include "Widget/OptionButton.h"
#include "Components/CheckBox.h"

void UGameplayOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LanguageOptionButton->OnIndexChanged.AddDynamic(this, &UGameplayOptionWidget::OnIndexChangedLanguageOptionButton);
	TiltBodyCheckBox->OnCheckStateChanged.AddDynamic(this, &UGameplayOptionWidget::OnCheckStateChangedTiltBodyCheckBox);
}

void UGameplayOptionWidget::UpdateGameSettings()
{
	LanguageOptionButton->SetIndex(static_cast<int32>(WIDGameUserSettings->Language));
	TiltBodyCheckBox->SetCheckedState(WIDGameUserSettings->bTiltBody ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
}

void UGameplayOptionWidget::OnIndexChangedLanguageOptionButton(const int32 Index)
{
	WIDGameUserSettings->Language = Index;
}

void UGameplayOptionWidget::OnCheckStateChangedTiltBodyCheckBox(const bool Value)
{
	WIDGameUserSettings->bTiltBody = Value;
}