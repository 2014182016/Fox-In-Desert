// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EDesertFoxMovementState : uint8
{
	Idle,
	Walking,
	Running,
	SlowWalking,
	Jumping,
};