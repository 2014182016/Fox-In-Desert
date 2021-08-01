// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "WIDGameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class WID_API UWIDGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	// {{ UGameUserSettings Interface
	virtual void SetToDefaults() override;
	// }} UGameUserSettings Interface

public:
	/** Applies game related settings */
	UFUNCTION(BlueprintCallable, Category = "Settings")
		virtual void ApplyGameSettings(class APlayerController* LocalPlayerController);

	// {{ Option Setting Function
	void SetMouseSensitivity(float Value);
	// }} Option Setting Function

public:
	// {{ Get Default Value Static Function
	static float GetDefaultMouseSensitivity();
	static float GetDefaultZoomDistance();
	// }} Get Default Value Static Function

public:
	/** Controls camera rotational speed by adjusting mouse sensitivity */
	UPROPERTY(config)
		float MouseSensitivity;

	/** Controls camera rotational speed by adjusting mouse sensitivity */
	UPROPERTY(config)
		float ZoomDistance;

protected:
	/** Limits the minimum and maximum value of mouse sensitivity */
	FVector2D MouseSensitivityRange = FVector2D(0.01f, 10.0f);

};
