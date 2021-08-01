// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WIDPlayerCameraManager.h"
#include "Core/WIDHUD.h"

void AWIDPlayerCameraManager::DoUpdateCamera(float DeltaTime)
{
	Super::DoUpdateCamera(DeltaTime);

	if (bEnableUIFading)
	{
		UpdateUIFade(FadeAmount);
	}
}

void AWIDPlayerCameraManager::StartCameraFadeWithUI(float FromAlpha, float ToAlpha, float Duration, FLinearColor Color, bool bShouldFadeAudio, bool bHoldWhenFinished)
{
	StartCameraFade(FromAlpha, ToAlpha, Duration, Color, bShouldFadeAudio, bHoldWhenFinished);

	bEnableUIFading = true;
}

void AWIDPlayerCameraManager::StopCameraFade()
{
	Super::StopCameraFade();

	if (bEnableUIFading)
	{
		UpdateUIFade(FadeAmount);
		bEnableUIFading = false;
	}
}

void AWIDPlayerCameraManager::UpdateUIFade(const float Amount)
{
	if (GetOwningHUD())
	{
		WID::FHudEventInfo HudEventInfo;
		HudEventInfo = 1.0f - Amount; // Invert fade amount
		GetOwningHUD()->UpdateHudEventWithValue(EHudType::All, EHudEvent::UpdateFade, HudEventInfo);
	}
}

AWIDHUD* AWIDPlayerCameraManager::GetOwningHUD()
{
	if (!WIDHUD)
	{
		WIDHUD = PCOwner->GetHUD<AWIDHUD>();
	}
	return WIDHUD;
}