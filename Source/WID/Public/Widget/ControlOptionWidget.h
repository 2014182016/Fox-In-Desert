// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/OptionDetailWidget.h"
#include "ControlOptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class WID_API UControlOptionWidget : public UOptionDetailWidget
{
	GENERATED_BODY()

protected:
	// {{ UUserWidget Interface
	virtual void NativeConstruct() override;
	// }} UUserWidget Interface

protected:
	// {{ UOptionDetailWidget Interface
	virtual void UpdateGameSettings() override;
	// }} UOptionDetailWidget Interface

	/** Called when mouse sensitivity slider is changed */
	UFUNCTION()
		void OnValueChangedMouseSensitivitySlider(const float Value);
	/** Called when invert mouse X axis checkbox state is changed */
	UFUNCTION()
		void OnCheckStateChangedInvertMouseXAxisCheckBox(const bool Value);
	/** Called when invert mouse Y axis checkbox state is changed */
	UFUNCTION()
		void OnCheckStateChangedInvertMouseYAxisCheckBox(const bool Value);
	/** Called when toggle sprint checkbox state is changed */
	UFUNCTION()
		void OnCheckStateChangedToggleSprintCheckBox(const bool Value);

protected:
	/** Adjust the mouse sensitivity setting using this slider */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class USlider* MouseSensitivitySlider;

	/** Adjust the invert mouse X axis setting using this check box */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UCheckBox* InvertMouseXAxisCheckBox;

	/** Adjust the invert mouse Y axis setting using this check box */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UCheckBox* InvertMouseYAxisCheckBox;

	/** Adjust the toggle sprint setting using this check box */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UCheckBox* ToggleSprintCheckBox;

};
