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
	bool CheckEventInfo(FHudEventInfo EvnetInfo);
	bool CheckEventInfo(FHudEventInfoList EvnetInfoList, int32 Index);

	/** Distance to inspect the floor */
	constexpr float CheckFloorDistance = 50.0f;
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
UENUM(BlueprintType, meta = (Bitflags))
enum class EHudType : uint8
{
	None			= 0 UMETA(Hidden),
	MainMenu		= 1 << 0,
	GameMenu		= 1 << 1,
	Loading			= 1 << 2,
	PlayerState		= 1 << 3,
	Option			= 1 << 4,
	Max				= 1 << 5 UMETA(Hidden),
};
ENUM_CLASS_FLAGS(EHudType);
ENUM_CLASS_FLAGS_INT(EHudType);
ENUM_RANGE_BY_COUNT(EHudType, EHudType::Max);

/** Type to distinguish events when calling event to the hud */
UENUM(BlueprintType, meta = (Bitflags))
enum class EHudEvent : uint8
{
	None				= 0 UMETA(Hidden),
	Update				= 1 << 1,
	Visibility			= 1 << 2,
	ToggleVisibility	= 1 << 3,
	UpdateStamina		= 1 << 4,
	UpdateHealth		= 1 << 5,
	Max					= 1 << 6 UMETA(Hidden),
};
ENUM_CLASS_FLAGS(EHudEvent);
ENUM_CLASS_FLAGS_INT(EHudEvent);
ENUM_RANGE_BY_COUNT(EHudEvent, EHudEvent::Max);

/** Each camera mode to control */
UENUM(BlueprintType)
enum class ECameraMode : uint8
{
	ControllerIndependent,
	ControllerDependent,
};