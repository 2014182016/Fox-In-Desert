// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/OptionDetailWidget.h"
#include "SoundOptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class WID_API USoundOptionWidget : public UOptionDetailWidget
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

	/** Called when master sound slider is changed */
	UFUNCTION()
		void OnValueChangedMasterSoundSlider(const float Value);
	/** Called when master sound checkbox state is changed */
	UFUNCTION()
		void OnCheckStateChangedMasterSoundCheckBox(const bool Value);
	/** Called when background sound slider is changed */
	UFUNCTION()
		void OnValueChangedBackgroundSoundSlider(const float Value);
	/** Called when background sound checkbox state is changed */
	UFUNCTION()
		void OnCheckStateChangedBackgroundSoundCheckBox(const bool Value);
	/** Called when effect sound slider is changed */
	UFUNCTION()
		void OnValueChangedEffectSoundSlider(const float Value);
	/** Called when effect sound checkbox state is changed */
	UFUNCTION()
		void OnCheckStateChangedEffectSoundCheckBox(const bool Value);

protected:
	/** Adjust the mouse sensitivity setting using this slider */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class USlider* MasterSoundSlider;

	/** Adjust the invert mouse X axis setting using this check box */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UCheckBox* MasterSoundCheckBox;

	/** Adjust the mouse sensitivity setting using this slider */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class USlider* BackgroundSoundSlider;

	/** Adjust the invert mouse X axis setting using this check box */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UCheckBox* BackgroundSoundCheckBox;

	/** Adjust the mouse sensitivity setting using this slider */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class USlider* EffectSoundSlider;

	/** Adjust the invert mouse X axis setting using this check box */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UCheckBox* EffectSoundCheckBox;

};
