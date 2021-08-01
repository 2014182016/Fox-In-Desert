// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WIDHUD.h"
#include "Widget/WIDUserWidget.h"
#include "Blueprint/UserWidget.h"

void AWIDHUD::BeginPlay()
{
	Super::BeginPlay();

	for (const FHudWidgetInfo& HudWidgetInfo : StartingWidgetInfoList)
	{
		AddWidgetByWidgetInfo(HudWidgetInfo);
	}
}

void AWIDHUD::Destroyed()
{
	Super::Destroyed();

	for (auto& CurrentWidgetInfo : CurrentWidgetList)
	{
		if (CurrentWidgetInfo.Value)
		{
			CurrentWidgetInfo.Value->RemoveFromViewport();
		}
	}

	CurrentWidgetList.Empty();
}

void AWIDHUD::AddWidget(const EHudType HudType, const TSubclassOf<UUserWidget>& NewWidgetClass, const ESlateVisibility Visibility)
{
	if (IsValid(PlayerOwner) && NewWidgetClass)
	{
		if (!FindWidget(HudType))
		{
			UUserWidget* NewWidget = CreateWidget<UUserWidget>(PlayerOwner, NewWidgetClass);
			if (NewWidget)
			{
				NewWidget->AddToViewport();
				NewWidget->SetVisibility(Visibility);
				CurrentWidgetList.Add(HudType, NewWidget);
			}
		}
	}
}

void AWIDHUD::AddWidgetByWidgetInfo(const FHudWidgetInfo& HudWidgetInfo)
{
	AddWidget(HudWidgetInfo.HudType, HudWidgetInfo.WidgetClass, HudWidgetInfo.StartVisibility);
}

void AWIDHUD::RemoveWidget(const EHudType HudType)
{
	UUserWidget* Widget = FindWidget(HudType);
	if (Widget)
	{
		Widget->RemoveFromViewport();
		CurrentWidgetList.Remove(HudType);
	}
}

UUserWidget* AWIDHUD::FindWidget(const EHudType HudType)
{
	UUserWidget** Widget = CurrentWidgetList.Find(HudType);
	if (Widget)
		return *Widget;
	return nullptr;
}

void AWIDHUD::UpdateHudEvent(const EHudType HudType, const EHudEvent HudEvent)
{
	WID::FHudEventInfo HudEventInfo;
	UpdateHudEventWithValue(HudType, HudEvent, HudEventInfo);
}

void AWIDHUD::UpdateHudEventWithValue(const EHudType HudType, const EHudEvent HudEvent, const WID::FHudEventInfo& HudEventInfo)
{
	WID::FHudEventInfoList HudEventInfoList;
	HudEventInfoList.Add(HudEventInfo);
	UpdateHudEventWithValue(HudType, HudEvent, HudEventInfoList);
}

void AWIDHUD::UpdateHudEventWithValue(const EHudType HudType, const EHudEvent HudEvent, const WID::FHudEventInfoList& HudEventInfoList)
{
	if (HudType == EHudType::All)
	{
		for (auto& CurrentWidgetInfo : CurrentWidgetList)
		{
			UWIDUserWidget* WIDWidget = Cast<UWIDUserWidget>(CurrentWidgetInfo.Value);
			if (WIDWidget)
			{
				WIDWidget->UpdateHudEvent(HudEvent, HudEventInfoList);
			}
		}
	}
	else
	{
		UWIDUserWidget* WIDWidget = Cast<UWIDUserWidget>(FindWidget(HudType));
		if (WIDWidget)
		{
			WIDWidget->UpdateHudEvent(HudEvent, HudEventInfoList);
		}
	}
}