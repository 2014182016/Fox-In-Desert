// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WIDTypes.h"
#include "Blueprint/UserWidget.h"
#include "WIDUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class WID_API UWIDUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** Receive events from the hud and do the desired actions in this widget */
	virtual void UpdateHudEvent(const EHudEvent HudEvent, const WID::FHudEventInfoList& HudEventInfoList);

};
