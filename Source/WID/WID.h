// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogWID, Log, All);

#define LogInfo (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define WID_LOG(Verbosity, Format, ...) UE_LOG(LogWID, Verbosity, TEXT("%s %s"), *LogInfo, *FString::Printf(Format, ##__VA_ARGS__))
#define LOG_SCREEN(Format, ...) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(Format, ##__VA_ARGS__))