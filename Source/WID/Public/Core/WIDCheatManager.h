// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "WIDCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class WID_API UWIDCheatManager : public UCheatManager
{
	GENERATED_BODY()
	
public:
	/** Toggle the function that prevents stamian from begin consumed */
	UFUNCTION(exec)
		virtual void InfiniteStamina();

	/** Change to desired speed, not the speed spcified in movement */
	UFUNCTION(exec)
		virtual void SetCheetSpeed(float DesiredSpeed);

};
