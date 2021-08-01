// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WIDUserWidget.h"
#include "GameMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class WID_API UGameMenuWidget : public UWIDUserWidget
{
	GENERATED_BODY()

public:
	// {{ UWIDUserWidget Interface
	virtual void UpdateHudEvent(const EHudEvent HudEvent, const WID::FHudEventInfoList& HudEventInfoList) override;
	// }} UWIDUserWidget Interface

protected:
	// {{ UUserWidget Interface
	virtual void NativeConstruct() override;
	// }} UUserWidget Interface

protected:
	/** Called when return to game button is clicked */
	UFUNCTION()
		void OnClickReturnToGameButton();
	/** Called when option button is clicked */
	UFUNCTION()
		void OnClickOptionButton();
	/** Called when exit button is clicked */
	UFUNCTION()
		void OnClickExitButton();
	
protected:
	/** Widget that allow you to change to other widgets */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UWidgetSwitcher* MenuWidgetSwitcher;

	/** Button to hidden this widget and return to game */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UButton* ReturnToGameButton;

	/** Button to change option widget */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UButton* OptionButton;

	/** Button to return to main menu */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UButton* ExitButton;
};
