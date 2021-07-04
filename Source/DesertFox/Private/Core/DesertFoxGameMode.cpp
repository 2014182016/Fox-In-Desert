// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/DesertFoxGameMode.h"
#include "Core/DesertFoxGameInstance.h"

void ADesertFoxGameMode::BeginPlay()
{
	Super::BeginPlay();

	UDesertFoxGameInstance* DesertFoxGameInstance = GetWorld()->GetGameInstance<UDesertFoxGameInstance>();
	if (DesertFoxGameInstance)
	{
		DesertFoxGameInstance->LoadGame();
	}
}

void ADesertFoxGameMode::SaveGame()
{
	UDesertFoxGameInstance* DesertFoxGameInstance = GetWorld()->GetGameInstance<UDesertFoxGameInstance>();
	if (DesertFoxGameInstance)
	{
		DesertFoxGameInstance->SaveGame();
	}
}