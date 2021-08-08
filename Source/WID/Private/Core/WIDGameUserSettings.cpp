// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WIDGameUserSettings.h"
#include "Core/WIdPlayerController.h"
#include "Core/WIDCharacter.h"
#include "Core/WIDMovementComponent.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"

UWIDGameUserSettings::UWIDGameUserSettings()
{
	MasterSoundMix = LoadObject<USoundMix>(nullptr, TEXT("/Game/WID/Sounds/MasterSoundMix"));
	MasterSoundClass = LoadObject<USoundClass>(nullptr, TEXT("/Game/WID/Sounds/MasterSound"));
	BackgroundSoundClass = LoadObject<USoundClass>(nullptr, TEXT("/Game/WID/Sounds/MusicSound"));
	EffectSoundClass = LoadObject<USoundClass>(nullptr, TEXT("/Game/WID/Sounds/SFXSound"));
}

void UWIDGameUserSettings::SetToDefaults()
{
	Super::SetToDefaults();

	// {{ Override game user settings from super class
	FullscreenMode = EWindowMode::Fullscreen;
	DesiredScreenWidth = GetDesktopResolution().X;
	DesiredScreenHeight = GetDesktopResolution().Y;
	// }} 

	MouseSensitivity = 5.0f;
	ZoomDistance = 300.0f;
	bInvertMouseXAxis = false;
	bInvertMouseYAxis = false;
	bToggleSprint = false;
	WindowMode = 2;
	ResolutionType = 0;
	Gamma = 2.2f;
	bVSync = false;
	GraphicQuality = 1;
	AAQuality = 1;
	PPQuality = 1;
	ShadowQuality = 1;
	TextureQuality = 1;
	EffectQuality = 1;
	Language = 0;
	bTiltBody = true;
	MasterSoundVolume = 1.0f;
	bMasterSoundEnabled = true;
	BackgroundSoundVolume = 1.0f;
	bBackgroundSoundEnabled = true;
	EffectSoundVolume = 1.0f;
	bEffectSoundEnabled = true;
}

void UWIDGameUserSettings::ApplySettings(bool bCheckForCommandLineOverrides)
{
	SetFullscreenMode(WID::ConvertIntToWindowMode(WindowMode));
	SetScreenResolution(WID::EResolution::ConvertIntToPoint(ResolutionType));

	Super::ApplySettings(bCheckForCommandLineOverrides);
}

void UWIDGameUserSettings::ApplyGameSettings(APlayerController* LocalPlayerController)
{
	if (!LocalPlayerController)
		return;

	AWIDPlayerController* WIDPlayerController = Cast<AWIDPlayerController>(LocalPlayerController);
	if (!IsValid(WIDPlayerController))
		return;

	WIDPlayerController->bToggleSprint = bToggleSprint;

	if (IsValid(WIDPlayerController->PlayerInput))
	{
		WIDPlayerController->PlayerInput->SetMouseSensitivity(MouseSensitivity);

		const float OldMouseSensitivityX = WIDPlayerController->PlayerInput->GetMouseSensitivityX();
		const float OldMouseSensitivityY = WIDPlayerController->PlayerInput->GetMouseSensitivityY();
		WIDPlayerController->PlayerInput->SetMouseSensitivity(bInvertMouseXAxis ? -OldMouseSensitivityX : OldMouseSensitivityX, bInvertMouseYAxis ? -OldMouseSensitivityY : OldMouseSensitivityY);
	}

	AWIDCharacter* WIDCharacter = WIDPlayerController->GetPawn<AWIDCharacter>();
	if (IsValid(WIDCharacter))
	{
		UWIDMovementComponent* WIDMovementComponent = Cast<UWIDMovementComponent>(WIDCharacter->GetCharacterMovement());
		if (WIDMovementComponent)
		{
			WIDMovementComponent->bTiltBody = bTiltBody;
		}
	}

	SetGamma(LocalPlayerController, Gamma);
	SetVSyncEnabled(bVSync);

	// Set overall graphic quality
	SetOverallScalabilityLevel(GraphicQuality);

	// Set each graphic quality
	SetAntiAliasingQuality(AAQuality);
	SetPostProcessingQuality(PPQuality);
	SetShadowQuality(ShadowQuality);
	SetTextureQuality(TextureQuality);
	SetVisualEffectQuality(EffectQuality);

	// Set sound volumes
	UGameplayStatics::SetSoundMixClassOverride(LocalPlayerController->GetWorld(), MasterSoundMix, MasterSoundClass, bMasterSoundEnabled ? MasterSoundVolume : 0.0f, 1.0f, 0.0f);
	UGameplayStatics::SetSoundMixClassOverride(LocalPlayerController->GetWorld(), MasterSoundMix, BackgroundSoundClass, bBackgroundSoundEnabled ? BackgroundSoundVolume : 0.0f, 1.0f, 0.0f);
	UGameplayStatics::SetSoundMixClassOverride(LocalPlayerController->GetWorld(), MasterSoundMix, EffectSoundClass, bEffectSoundEnabled ? EffectSoundVolume : 0.0f, 1.0f, 0.0f);
	UGameplayStatics::PushSoundMixModifier(LocalPlayerController->GetWorld(), MasterSoundMix);
}

#if WITH_EDITOR
void UWIDGameUserSettings::RestoreForEditor(APlayerController* LocalPlayerController)
{
	if (!LocalPlayerController)
		return;

	AWIDPlayerController* WIDPlayerController = Cast<AWIDPlayerController>(LocalPlayerController);
	if (!IsValid(WIDPlayerController))
		return;

	SetGamma(LocalPlayerController, 2.2f);
	SetOverallScalabilityLevel(1);
}
#endif // WITH_EDITOR

void UWIDGameUserSettings::SetMouseSensitivityInRange(float Value)
{
	MouseSensitivity = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), MouseSensitivityRange, Value);
}

float UWIDGameUserSettings::GetMouseSensitivityInRange() const
{
	return FMath::GetMappedRangeValueClamped(MouseSensitivityRange, FVector2D(0.0f, 1.0f), MouseSensitivity);
}

void UWIDGameUserSettings::SetBrightnessInRange(float Value)
{
	// Convert brightness to gamma
	Gamma = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), GammaRange, Value);
}

float UWIDGameUserSettings::GetBrightnessInRange() const
{
	// Convert gamma to brightness
	return FMath::GetMappedRangeValueClamped(GammaRange, FVector2D(0.0f, 1.0f), Gamma);
}

void UWIDGameUserSettings::SetGamma(APlayerController* LocalPlayerController, const float Value)
{
	if (IsValid(LocalPlayerController))
	{
		TArray<FStringFormatArg> Args;
		Args.Emplace(Value);
		LocalPlayerController->ConsoleCommand(FString::Format(TEXT("Gamma {0}"), Args));
	}
}