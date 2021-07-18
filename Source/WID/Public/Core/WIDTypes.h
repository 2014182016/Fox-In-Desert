// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WIDTypes.generated.h"

/** Specify a function that does nothing */
#define EmptyFunction {}

/** The state of character movement */
UENUM(BlueprintType)
enum class EWIDMovementState : uint8
{
	None,
	Idle,
	Walking,
	Running,
	SlowWalking,
	Jumping,
};

/** Type to distinguish widgets attached to the hud */
UENUM(BlueprintType)
enum class EHudType : uint8
{
	MainMenu,
	PlayerState,
	All,
};

/** Type to distinguish events when calling event to the hud */
UENUM(BlueprintType)
enum class EHudEvent : uint8
{
	UpdateInfo,
	Visibility,
};

