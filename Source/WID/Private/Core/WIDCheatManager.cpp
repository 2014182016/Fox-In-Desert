// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WIDCheatManager.h"
#include "Core/WIDPlayerState.h"
#include "../WID.h"

void UWIDCheatManager::InfiniteStamina()
{
	AWIDPlayerState* WIDPlayerState = GetOuterAPlayerController()->GetPlayerState<AWIDPlayerState>();
	if (IsValid(WIDPlayerState))
	{
		WIDPlayerState->bInfiniteStamina = !WIDPlayerState->bInfiniteStamina;
		WID_LOG(Display, TEXT("Set InfiniteStamina : %s"), WIDPlayerState->bInfiniteStamina ? TEXT("true") : TEXT("false"));
	}
}