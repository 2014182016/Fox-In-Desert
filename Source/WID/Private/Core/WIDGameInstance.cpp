// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WIDGameInstance.h"
#include "../WID.h"
#include "Core/WIDSaveGame.h"
#include "Kismet/GameplayStatics.h"

UWIDSaveGame* UWIDGameInstance::SaveGame()
{
	UWIDSaveGame* WIDSaveGame = Cast<UWIDSaveGame>(UGameplayStatics::CreateSaveGameObject(UWIDSaveGame::StaticClass()));
	if (WIDSaveGame)
	{
	}
	else
	{
		WID_LOG(Warning, TEXT("%s is nullptr. Failed Save Game"), *SaveSlotName);
	}

	UGameplayStatics::SaveGameToSlot(WIDSaveGame, SaveSlotName, 0);

	return WIDSaveGame;
}

UWIDSaveGame* UWIDGameInstance::LoadGame()
{
	UWIDSaveGame* WIDSaveGame = Cast<UWIDSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (WIDSaveGame)
	{
	}
	else
	{
		WID_LOG(Warning, TEXT("%s does not exist. Failed Load Game"), *SaveSlotName);
	}

	return WIDSaveGame;
}