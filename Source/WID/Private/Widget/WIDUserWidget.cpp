// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WIDUserWidget.h"

void UWIDUserWidget::UpdateHudEvent(const EHudEvent HudEvent, const WID::FHudEventInfoList& HudEventInfoList)
{
	switch (HudEvent)
	{
	case EHudEvent::Visibility:
		if (WID::CheckEventInfo(HudEventInfoList, 0))
		{
			ESlateVisibility NewVisibility = ESlateVisibility(HudEventInfoList[0].GetValue<int32>());
			SetVisibility(NewVisibility);
		}
		break;
	case EHudEvent::ToggleVisibility:
		SetVisibility(IsVisible() ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
		break;
	case EHudEvent::UpdateFade:
		if (WID::CheckEventInfo(HudEventInfoList, 0))
		{
			const float FadeAmount = HudEventInfoList[0].GetValue<float>();
			SetRenderOpacity(FadeAmount);
		}
		break;
	}
}