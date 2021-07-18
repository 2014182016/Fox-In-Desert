// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WIDGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WID_API UWIDGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	/** Save the current game data */
	UFUNCTION(BlueprintCallable)
		class UWIDSaveGame* SaveGame();

	/** Load the lastest game data */
	UFUNCTION(BlueprintCallable)
		class UWIDSaveGame* LoadGame();

private:
	/** Slot name to save, only one slot exists */
	UPROPERTY(EditDefaultsOnly, Category = "SaveData", meta = (AllowPrivateAccess = true))
		FString SaveSlotName;

};
