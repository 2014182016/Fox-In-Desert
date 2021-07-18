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
	/** Save the current game data using USaveGame */
	UFUNCTION(exec)
		void SaveGame();

protected:
	virtual void BeginPlay() override;

};



