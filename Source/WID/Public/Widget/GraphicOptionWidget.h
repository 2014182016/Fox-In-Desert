// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/OptionDetailWidget.h"
#include "GraphicOptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class WID_API UGraphicOptionWidget : public UOptionDetailWidget
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

	/** Called when window mode option button is clicked */
	UFUNCTION()
		void OnIndexChangedWindowModeOptionButton(const int32 Index);
	/** Called when resolution option button is clicked */
	UFUNCTION()
		void OnIndexChangedResolutionOptionButton(const int32 Index);
	/** Called when brightness slider is changed */
	UFUNCTION()
		void OnValueChangedMouseBrightnessSlider(const float Value);
	/** Called when toggle vsync checkbox state is changed */
	UFUNCTION()
		void OnCheckStateChangedVSyncCheckBox(const bool Value);
	/** Called when graphic quality option button is clicked */
	UFUNCTION()
		void OnIndexChangedGraphicQualityOptionButton(const int32 Index);
	/** Called when AA option button is clicked */
	UFUNCTION()
		void OnIndexChangedAAOptionButton(const int32 Index);
	/** Called when PP option button is clicked */
	UFUNCTION()
		void OnIndexChangedPPOptionButton(const int32 Index);
	/** Called when shadow option button is clicked */
	UFUNCTION()
		void OnIndexChangedShadowQualityOptionButton(const int32 Index);
	/** Called when texture option button is clicked */
	UFUNCTION()
		void OnIndexChangedTextureQualityOptionButton(const int32 Index);
	/** Called when effect option button is clicked */
	UFUNCTION()
		void OnIndexChangedEffectQualityOptionButton(const int32 Index);

protected:
	/** Control the window mode through this button */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UOptionButton* WindowModeOptionButton;

	/** Control the resolution through this button */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UOptionButton* ResolutionOptionButton;

	/** Control the brightness through this slider */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class USlider* BrightnessSlider;

	/** Adjust the toggle sprint setting using this check box */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UCheckBox* VSyncCheckBox;

	/** Control the graphic quality through this button */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UOptionButton* GraphicQualityOptionButton;

	/** Control the anti aliasing quality through this button */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UOptionButton* AAOptionButton;

	/** Control the post process quality through this button */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UOptionButton* PPOptionButton;

	/** Control the shadow quality through this button */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UOptionButton* ShadowQualityOptionButton;

	/** Control the texture quality through this button */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UOptionButton* TextureQualityOptionButton;

	/** Control the effect quality through this button */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UOptionButton* EffectQualityOptionButton;

};
