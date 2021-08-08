// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WIDTypes.h"
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
	UWIDGameUserSettings();

	// {{ UGameUserSettings Interface
	virtual void ApplySettings(bool bCheckForCommandLineOverrides) override;
	virtual void SetToDefaults() override;
	// }} UGameUserSettings Interface

public:
	/** Applies game related settings */
	UFUNCTION(BlueprintCallable, Category = "Settings")
		virtual void ApplyGameSettings(class APlayerController* LocalPlayerController);

#if WITH_EDITOR
	/** At the end of the PIE, restore the basic setting of the engine */
	virtual void RestoreForEditor(class APlayerController* LocalPlayerController);
#endif // WITH_EDITOR

	/** Set gamma to control the brightness of the screen */
	void SetGamma(class APlayerController* LocalPlayerController, const float Value);

	// {{ Option Setting Function
	void SetMouseSensitivityInRange(float Value);
	float GetMouseSensitivityInRange() const;
	void SetBrightnessInRange(float Value);
	float GetBrightnessInRange() const;
	// }} Option Setting Function

public: // controls
	/** Controls camera rotational speed by adjusting mouse sensitivity */
	UPROPERTY(config)
		float MouseSensitivity;

	/** Controls camera rotational speed by adjusting mouse sensitivity */
	UPROPERTY(config)
		float ZoomDistance;

	/** The adjustment value of mouse X is inverted */
	UPROPERTY(config)
		uint8 bInvertMouseXAxis : 1;

	/** The adjustment value of mouse Y is inverted */
	UPROPERTY(config)
		uint8 bInvertMouseYAxis : 1;

	/** Toggle the run to control it */
	UPROPERTY(config)
		uint8 bToggleSprint : 1;

public: // grpahics
	/** Specify window mode through this variable */
	UPROPERTY(config)
		uint32 WindowMode;

	/** Specify reosolution through this variable and the index is converted from enum to point type */
	UPROPERTY(config)
		uint32 ResolutionType;

	/** Adjust the brightness of the screen through gamma */
	UPROPERTY(config)
		float Gamma;

	/** Adjust the vertical synchronization */
	UPROPERTY(config)
		uint8 bVSync : 1;

	/** Set all grahpic settings at once */
	UPROPERTY(config)
		uint32 GraphicQuality;

	/** Adjust the anti aliasing quality */
	UPROPERTY(config)
		uint32 AAQuality;

	/** Adjust the post process quality */
	UPROPERTY(config)
		uint32 PPQuality;

	/** Adjust the shadow quality */
	UPROPERTY(config)
		uint32 ShadowQuality;

	/** Adjust the texture quality */
	UPROPERTY(config)
		uint32 TextureQuality;

	/** Adjust the visual effect quality */
	UPROPERTY(config)
		uint32 EffectQuality;

public: // sounds
	/** Adjust the master sound volume */
	UPROPERTY(config)
		float MasterSoundVolume;

	/** Enable the master sound volume, if not, volume is not applied */
	UPROPERTY(config)
		uint8 bMasterSoundEnabled : 1;

	/** Adjust the background sound volume */
	UPROPERTY(config)
		float BackgroundSoundVolume;

	/** Enable the background sound volume, if not, volume is not applied */
	UPROPERTY(config)
		uint8 bBackgroundSoundEnabled : 1;

	/** Adjust the effect sound volume */
	UPROPERTY(config)
		float EffectSoundVolume;

	/** Enable the effect sound volume, if not, volume is not applied */
	UPROPERTY(config)
		uint8 bEffectSoundEnabled : 1;

public: // gameplays
	/** Localization is applied to UI by changing language */
	UPROPERTY(config)
		uint32 Language;

	/** Tilt according to the normal direction of the floor */
	UPROPERTY(config)
		uint8 bTiltBody : 1;

protected:
	/** Limits the minimum and maximum value of mouse sensitivity */
	FVector2D MouseSensitivityRange = FVector2D(0.01f, 10.0f);

	/** Limits the minimum and maximum value of gamma */
	FVector2D GammaRange = FVector2D(0.5f, 5.0f);

private:
	UPROPERTY(Transient)
		class USoundMix* MasterSoundMix;

	UPROPERTY(Transient)
		class USoundClass* MasterSoundClass;

	UPROPERTY(Transient)
		class USoundClass* BackgroundSoundClass;

	UPROPERTY(Transient)
		class USoundClass* EffectSoundClass;

};
