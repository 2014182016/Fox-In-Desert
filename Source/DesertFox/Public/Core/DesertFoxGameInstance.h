// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DesertFoxGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DESERTFOX_API UDesertFoxGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		class UDesertFoxSaveGame* SaveGame();

	UFUNCTION(BlueprintCallable)
		class UDesertFoxSaveGame* LoadGame();

private:
	UPROPERTY(EditDefaultsOnly, Category = "SaveData", meta = (AllowPrivateAccess = true))
		FString SaveSlotName;

};
