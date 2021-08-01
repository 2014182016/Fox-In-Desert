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

protected:
	/** Adjust the mouse sensitivity setting using this slider */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class USlider* MouseSensitivitySlider;

};
