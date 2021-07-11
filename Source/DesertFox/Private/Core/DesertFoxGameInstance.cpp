// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DesertFoxGameInstance.h"
#include "Core/DesertFoxSaveGame.h"
#include "Kismet/GameplayStatics.h"

UDesertFoxSaveGame* UDesertFoxGameInstance::SaveGame()
{
	UDesertFoxSaveGame* DesertFoxSaveGame = Cast<UDesertFoxSaveGame>(UGameplayStatics::CreateSaveGameObject(UDesertFoxSaveGame::StaticClass()));
	if (DesertFoxSaveGame)
	{
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is nullptr. Failed Save Game"), *SaveSlotName);
	}

	UGameplayStatics::SaveGameToSlot(DesertFoxSaveGame, SaveSlotName, 0);

	return DesertFoxSaveGame;
}

UDesertFoxSaveGame* UDesertFoxGameInstance::LoadGame()
{
	UDesertFoxSaveGame* DesertFoxSaveGame = Cast<UDesertFoxSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (DesertFoxSaveGame)
	{
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is nullptr. Failed Load Game"), *SaveSlotName);
	}

	return DesertFoxSaveGame;
}