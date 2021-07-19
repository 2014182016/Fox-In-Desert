// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
}

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
UENUM(BlueprintType, meta = (Bitflags))
enum class EHudType : uint8
{
	MainMenu		= 0,
	PlayerState		= 1 << 0,
	Max				= 1 << 1 UMETA(Hidden),
};
ENUM_CLASS_FLAGS(EHudType);
ENUM_CLASS_FLAGS_INT(EHudType);
ENUM_RANGE_BY_COUNT(EHudType, EHudType::Max);

/** Type to distinguish events when calling event to the hud */
UENUM(BlueprintType, meta = (Bitflags))
enum class EHudEvent : uint8
{
	Update				= 0,
	Visibility			= 1 << 0,
	ToggleVisibility	= 1 << 1,
	Max					= 1 << 2 UMETA(Hidden),
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

