// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WIDTypes.h"
#include "GameFramework/HUD.h"
#include "WIDHUD.generated.h"

USTRUCT(BlueprintType)
struct FHudWidgetInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		EHudType HudType;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> WidgetClass;

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
	UFUNCTION(BlueprintCallable, Category = "Widget")
		virtual void AddWidget(const EHudType HudType, const TSubclassOf<UUserWidget>& NewWidgetClass, const ESlateVisibility Visibility);

	UFUNCTION(BlueprintCallable, Category = "Widget")
		virtual void RemoveWidget(const EHudType HudType);

	UFUNCTION(BlueprintCallable, Category = "Widget")
		virtual class UUserWidget* FindWidget(const EHudType HudType);

	UFUNCTION(BlueprintCallable, Category = "HudEvent")
		void UpdateHudEvent(const EHudType HudType, const EHudEvent HudEvent);

protected:
	// {{ AActor Interface
	virtual void BeginPlay() override;
	// }} AActor Interface

protected:
	virtual void AddWidgetByWidgetInfo(const FHudWidgetInfo& HudWidgetInfo);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (AllowPrivateAccess = true))
		TArray<FHudWidgetInfo> StartingWidgetInfoList;

protected:
	UPROPERTY(Transient, BlueprintReadOnly)
		TMap<EHudType, class UUserWidget*> CurrentWidgetList;

};
