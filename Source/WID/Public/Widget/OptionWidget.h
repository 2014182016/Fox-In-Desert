// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WIDUserWidget.h"
#include "OptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class WID_API UOptionWidget : public UWIDUserWidget
{
	GENERATED_BODY()

protected:
	// {{ UUserWidget Interface
	virtual void NativeConstruct() override;
	// }} UUserWidget Interface

public:
	/** The current option settings is reflected in each detail option widget */
	void UpdateOptionSettings();

protected:
	/** Called when apply button is clicked */
	UFUNCTION()
		void OnClickApplyButton();
	/** Called when set to default button is clicked */
	UFUNCTION()
		void OnClickSetToDefaultButton();
	/** Called when return button is clicked */
	UFUNCTION()
		void OnClickReturnButton();
	/** Called when gameplay option button is clicked */
	UFUNCTION()
		void OnClickGameplayOptionButton();
	/** Called when control option button is clicked */
	UFUNCTION()
		void OnClickControlOptionButton();
	/** Called when graphic option button is clicked */
	UFUNCTION()
		void OnClickGraphicOptionButton();
	/** Called when sound option button is clicked */
	UFUNCTION()
		void OnClickSoundOptionButton();
	
protected:
	/** Widget that allow you to change to other option widgets */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UWidgetSwitcher* OptionWidgetSwitcher;

	/** Button to apply the current options from game user settings */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UButton* ApplyButton;

	/** Button to return option settings to default value */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UButton* SetToDefaultButton;

	/** Button to return to main menu */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UButton* ReturnButton;

	/** Button to change to an gameplay option widget */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UButton* GameplayOptionButton;

	/** Button to change to an control option widget */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UButton* ControlOptionButton;

	/** Button to change to an graphic option widget */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UButton* GraphicOptionButton;

	/** Button to change to an sound option widget */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UButton* SoundOptionButton;

protected:
	UPROPERTY(Transient)
		class UWIDGameUserSettings* WIDGameUserSettings;

};
