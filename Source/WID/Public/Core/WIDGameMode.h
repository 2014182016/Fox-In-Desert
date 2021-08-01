// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WIDGameMode.generated.h"

UCLASS()
class AWIDGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** Go to the level in LevelPath. Function defined to use seamless level */
	UFUNCTION(BlueprintCallable)
		void GoToNextLevel(const FName LevelPath = NAME_None, const bool bDoNoUseSeamlessLevel = false);

protected:
	// {{ AActor Interface
	virtual void BeginPlay() override;
	// }} AActor Interface

protected:
	/** Path to move to the next level comes in at the start of the game */
	FString NextLevelPath;

};



