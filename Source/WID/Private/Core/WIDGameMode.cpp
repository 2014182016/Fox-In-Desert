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

void AWIDGameMode::GoToNextLevel(const FName LevelPath, const bool bDoNoUseSeamlessLevel)
{
	if (LevelPath.GetStringLength() > 0)
	{
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			if (Iterator->Get())
			{
				Iterator->Get()->ClientTravel(LevelPath.ToString(), ETravelType::TRAVEL_Relative, bDoNoUseSeamlessLevel ? false : bUseSeamlessTravel);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NextLevelPath is not set"));
	}
}