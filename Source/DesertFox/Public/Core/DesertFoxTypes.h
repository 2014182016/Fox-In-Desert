// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DesertFoxTypes.generated.h"

/* Specify a function that does nothing */
#define EmptyFunction {}

/* The state of character movement */
UENUM(BlueprintType)
enum class EDesertFoxMovementState : uint8
{
	None,
	Idle,
	Walking,
	Running,
	SlowWalking,
	Jumping,
};