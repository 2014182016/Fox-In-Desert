// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionalWrapper.h"
#include "WIDTypes.generated.h"

/** Specify a function that does nothing */
#define EmptyFunction {}

/** Defines all bitwise operators related to int32 for enum classes so it can be available without need for a static_cast */
#define ENUM_CLASS_FLAGS_INT(Enum) \
	inline constexpr bool operator| (Enum& Lhs, int32 Rhs) { return (static_cast<int32>(Lhs) | Rhs); } \
	inline constexpr bool operator& (Enum& Lhs, int32 Rhs) { return (static_cast<int32>(Lhs) & Rhs); } \
	inline constexpr bool operator^ (Enum& Lhs, int32 Rhs) { return (static_cast<int32>(Lhs) ^ Rhs); }

namespace WID
{
	/** Data type to use for the Hud Event Information */
	using FHudEventInfo = FVariant;
	using FHudEventInfoList = TArray<FVariant>;

	/** Check that the Hud Event Information is delivered correctly */
	bool CheckEventInfo(const FHudEventInfo& EvnetInfo);
	bool CheckEventInfo(const FHudEventInfoList& EvnetInfoList, int32 Index);

	/** Distance to inspect the floor for footstep */
	constexpr float CheckFootstepDistance = 100.0f;
	/** Distance to inspect the floor for falling animation */
	constexpr float CheckFallingDistance = 10000.0f;
	/** Distance to inspect the floor for character rotation */
	constexpr float CheckWalkingDistance = 50.0f;
	/** Distance to raise a certain value when foostep because foot digs into the ground */
	constexpr float CheckFootstepUpDistance = 50.0f;
}

/** The state of character movement */
UENUM()
enum class EWIDMovementState : uint8
{
	None,
	Idle,
	Walking,
	Running,
	SlowWalking,
	Jumping,
	Sleeping,
};

/** Type to distinguish widgets attached to the hud */
UENUM()
enum class EHudType : uint8
{
	MainMenu,
	GameMenu,
	Loading,
	PlayerState,
	Option,
	All,
};

/** Type to distinguish events when calling event to the hud */
UENUM(BlueprintType)
enum class EHudEvent : uint8
{
	Update,
	Visibility,
	ToggleVisibility,
	UpdateStamina,
	UpdateHealth,
	WidgetSwitcher,
	UpdateGameSettings,
	UpdateFade,
	UpdateStaminaState,
};

/** Each camera mode to control */
UENUM()
enum class ECameraMode : uint8
{
	ControllerIndependent,
	ControllerDependent,
};

/** Enumeration defining the input mode of controller */
UENUM()
enum class EInputMode : uint8
{
	GameOnly,
	UIOnly,
	GameAndUI,
};

/** Enumeration the current state of statmina */
UENUM()
enum class EStaminaState : uint8
{
	Normal,
	Exhaustion,
};