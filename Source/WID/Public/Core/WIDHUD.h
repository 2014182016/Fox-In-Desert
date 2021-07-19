// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WIDTypes.h"
#include "GameFramework/HUD.h"
#include "WIDHUD.generated.h"

/** Information required for the widget in hud */
USTRUCT(BlueprintType)
struct FHudWidgetInfo
{
	GENERATED_USTRUCT_BODY()

public:
	/** Type to distinguish each widget */
	UPROPERTY(EditDefaultsOnly)
		EHudType HudType;

	/** The widget class to apply to this type */
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> WidgetClass;

	/** Visibility to apply at startup */
	UPROPERTY(EditDefaultsOnly)
		ESlateVisibility StartVisibility;
};

/**
 * 
 */
UCLASS()
class WID_API AWIDHUD : public AHUD
{
	GENERATED_BODY()

public:
	/** Create a new widget for this type and attach it to viewport. Only one widget can be attached to that type */
	UFUNCTION(BlueprintCallable, Category = "Widget")
		virtual void AddWidget(const EHudType HudType, const TSubclassOf<UUserWidget>& NewWidgetClass, const ESlateVisibility Visibility);

	/** Find and remove widget of this type that have already been attached */
	UFUNCTION(BlueprintCallable, Category = "Widget")
		virtual void RemoveWidget(const EHudType HudType);

	/** Find widget of this type and return it to the form of a UUserWidget */
	UFUNCTION(BlueprintCallable, Category = "Widget")
		virtual class UUserWidget* FindWidget(const EHudType HudType);

	/** Call each event to the widget you want through the hud */
	UFUNCTION(BlueprintCallable, Category = "HudEvent")
		void UpdateHudEvent(const EHudType HudType, const EHudEvent HudEvent);

	/** Call event to multiple widgets at once using flags */
	UFUNCTION(BlueprintCallable, Category = "HudEvent")
		void UpdateHudEventByTypeFlags(
			UPARAM(meta = (BitMask, BitmaskEnum = EHudType)) const int32 TypeFlags,
			const EHudEvent HudEvent);

	/** Call multiple events at once using flags */
	UFUNCTION(BlueprintCallable, Category = "HudEvent")
		void UpdateHudEventByEventFlags(
			const EHudType HudType, 
			UPARAM(meta = (BitMask, BitmaskEnum = EHudEvent)) const int32 EventFlags);

	/** Call multiple events to multiple widgets at once using flags. Don't use this function if you can */
	UFUNCTION(BlueprintCallable, Category = "HudEvent")
		void UpdateHudEventAllFlags(
			UPARAM(meta = (BitMask, BitmaskEnum = EHudType)) const int32 TypeFlags,
			UPARAM(meta = (BitMask, BitmaskEnum = EHudEvent)) const int32 EventFlags);

	/** Deliver each event and information to the widget you want through the hud */
	void UpdateHudEventWithValue(const EHudType HudType, const EHudEvent HudEvent, const WID::FHudEventInfo& HudEventInfo);
	void UpdateHudEventWithValue(const EHudType HudType, const EHudEvent HudEvent, const WID::FHudEventInfoList& HudEventInfoList);

protected:
	// {{ AActor Interface
	virtual void BeginPlay() override;
	// }} AActor Interface

protected:
	/** Use FHudWidgetInfo to attach the widget */
	virtual void AddWidgetByWidgetInfo(const FHudWidgetInfo& HudWidgetInfo);

protected:
	/** WidgetInfo to attach to viewport at the start of the game */
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (AllowPrivateAccess = true))
		TArray<FHudWidgetInfo> StartingWidgetInfoList;

protected:
	/** Widgget currently attached to viewport */
	UPROPERTY(Transient, BlueprintReadOnly)
		TMap<EHudType, class UUserWidget*> CurrentWidgetList;

};
