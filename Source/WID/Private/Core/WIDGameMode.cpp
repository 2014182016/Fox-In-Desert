// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/WIDGameMode.h"
#include "Core/WIDGameInstance.h"

void AWIDGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWIDGameInstance* WIDGameInstance = GetWorld()->GetGameInstance<UWIDGameInstance>();
	if (WIDGameInstance)
	{
		WIDGameInstance->LoadGame();
	}
}

void AWIDGameMode::SaveGame()
{
	UWIDGameInstance* WIDGameInstance = GetWorld()->GetGameInstance<UWIDGameInstance>();
	if (WIDGameInstance)
	{
		WIDGameInstance->SaveGame();
	}
}