// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DesertFoxGameMode.generated.h"

UCLASS()
class ADesertFoxGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(exec)
		void SaveGame();

protected:
	virtual void BeginPlay() override;

};



