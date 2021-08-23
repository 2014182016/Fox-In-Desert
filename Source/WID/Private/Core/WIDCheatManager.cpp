// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WIDCheatManager.h"
#include "Core/WIDPlayerState.h"
#include "Core/WIDCharacter.h"
#include "Core/WIDMovementComponent.h"
#include "../WID.h"

void UWIDCheatManager::InfiniteStamina()
{
#if !UE_BUILD_SHIPPING
	AWIDPlayerState* WIDPlayerState = GetOuterAPlayerController()->GetPlayerState<AWIDPlayerState>();
	if (IsValid(WIDPlayerState))
	{
		WIDPlayerState->bInfiniteStamina = !WIDPlayerState->bInfiniteStamina;
		WID_LOG(Display, TEXT("Set InfiniteStamina : %s"), WIDPlayerState->bInfiniteStamina ? TEXT("true") : TEXT("false"));
	}
#endif // !UE_BUILD_SHIPPING
}

void UWIDCheatManager::SetCheetSpeed(float DesiredSpeed)
{
#if !UE_BUILD_SHIPPING
	AWIDCharacter* WIDCharacter = GetOuterAPlayerController()->GetPawn<AWIDCharacter>();
	if (IsValid(WIDCharacter))
	{
		UWIDMovementComponent* WIDMovementComponent = Cast<UWIDMovementComponent>(WIDCharacter->GetCharacterMovement());
		if (WIDMovementComponent)
		{
			WIDMovementComponent->CheatSpeed = DesiredSpeed;
			WID_LOG(Display, TEXT("Set Cheet Speed : %f"), DesiredSpeed);
		}
	}
#endif // !UE_BUILD_SHIPPING
}