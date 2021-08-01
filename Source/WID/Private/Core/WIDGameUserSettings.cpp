// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WIDGameUserSettings.h"
#include "Core/WIdPlayerController.h"
#include "GameFramework/PlayerInput.h"

void UWIDGameUserSettings::SetToDefaults()
{
	Super::SetToDefaults();

	MouseSensitivity = GetDefaultMouseSensitivity();
	ZoomDistance = GetDefaultZoomDistance();
}

void UWIDGameUserSettings::ApplyGameSettings(APlayerController* LocalPlayerController)
{
	if (!LocalPlayerController)
		return;

	AWIDPlayerController* WIDPlayerController = Cast<AWIDPlayerController>(LocalPlayerController);
	if (!WIDPlayerController)
		return;

	if (WIDPlayerController->PlayerInput)
	{
		WIDPlayerController->PlayerInput->SetMouseSensitivity(MouseSensitivity);
	}
}

void UWIDGameUserSettings::SetMouseSensitivity(float Value)
{
	MouseSensitivity = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), MouseSensitivityRange, Value);
}

float UWIDGameUserSettings::GetDefaultMouseSensitivity()
{
	return 5.0f;
}

float UWIDGameUserSettings::GetDefaultZoomDistance()
{
	return 300.0f;
}