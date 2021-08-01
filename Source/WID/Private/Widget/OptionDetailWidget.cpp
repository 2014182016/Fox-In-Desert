// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/OptionDetailWidget.h"
#include "../WID.h"

void UOptionDetailWidget::UpdateHudEvent(const EHudEvent HudEvent, const WID::FHudEventInfoList& HudEventInfoList)
{
	Super::UpdateHudEvent(HudEvent, HudEventInfoList);

	switch (HudEvent)
	{
	case EHudEvent::UpdateGameSettings:
		UpdateGameSettings();
		break;
	}
}

void UOptionDetailWidget::NativeConstruct()
{
	Super::NativeConstruct();

	WIDGameUserSettings = Cast<UWIDGameUserSettings>(GEngine->GetGameUserSettings());
	verifyf(WIDGameUserSettings != nullptr, TEXT("Does not exist Game User Settings"));
}