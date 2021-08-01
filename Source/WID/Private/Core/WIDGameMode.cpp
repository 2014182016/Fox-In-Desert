// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/WIDGameMode.h"
#include "Kismet/GameplayStatics.h"

void AWIDGameMode::BeginPlay()
{
	Super::BeginPlay();

	FString ParsedNextLevel = UGameplayStatics::ParseOption(OptionsString, TEXT("NextLevel"));
	if (ParsedNextLevel.Len() > 0)
	{
		NextLevelPath = ParsedNextLevel;
	}
}

void AWIDGameMode::GoToNextLevel(const FName LevelPath, const bool bDoNoUseSeamlessLevel)
{
	FString TravelLevelPath;

	if (LevelPath.GetStringLength() > 0 && !LevelPath.IsNone())
	{
		TravelLevelPath = LevelPath.ToString();
	}
	else if (NextLevelPath.Len() > 0)
	{
		TravelLevelPath = NextLevelPath;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelPath is not set"));
		return;
	}

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		if (Iterator->Get())
		{
			Iterator->Get()->ClientTravel(TravelLevelPath, ETravelType::TRAVEL_Relative, bDoNoUseSeamlessLevel ? false : bUseSeamlessTravel);
		}
	}
}