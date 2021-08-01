// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WIDGameUserSettings.h"
#include "Widget/WIDUserWidget.h"
#include "OptionDetailWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class WID_API UOptionDetailWidget : public UWIDUserWidget
{
	GENERATED_BODY()
	
public:
	// {{ UWIDUserWidget Interface
	virtual void UpdateHudEvent(const EHudEvent HudEvent, const WID::FHudEventInfoList& HudEventInfoList) override;
	// }} UWIDUserWidget Interface

	/** Update the widget if data has been changed by user game settings */
	virtual void UpdateGameSettings() PURE_VIRTUAL(UOptionDetailWidget::UpdateGameSettings, );

protected:
	// {{ UUserWidget Interface
	virtual void NativeConstruct() override;
	// }} UUserWidget Interface

protected:
	UPROPERTY(Transient)
		class UWIDGameUserSettings* WIDGameUserSettings;

};
