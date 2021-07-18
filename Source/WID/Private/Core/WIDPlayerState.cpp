// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WIDPlayerState.h"
#include "Core/WIDCharacter.h"
#include "Core/WIDMovementComponent.h"

AWIDPlayerState::AWIDPlayerState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWIDPlayerState::BeginPlay()
{
	Super::BeginPlay();

	CurrentStamina = MaxStamina;
	CurrentHealth = MaxHealth;
}

void AWIDPlayerState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateStamina(DeltaSeconds);
}

void AWIDPlayerState::UpdateStamina(float DeltaSeconds)
{
	AWIDCharacter* WIDCharacter = GetPawn<AWIDCharacter>();
	if (WIDCharacter == nullptr)
		return;

	UWIDMovementComponent* WIDMovement = Cast<UWIDMovementComponent>(WIDCharacter->GetMovementComponent());
	if (WIDMovement == nullptr)
		return;

	if (WIDMovement->IsRunning())
	{
		if (CurrentStamina > 0.0f)
		{
			CurrentStamina -= StaminaConsumptionPerSecond * DeltaSeconds;
			if (CurrentStamina <= 0.0f)
			{
				CurrentStamina = 0.0f;
				RunOutStamina(WIDCharacter);
			}
		}
	}
	else if(!WIDMovement->IsJumping())
	{
		if (CurrentStamina < MaxStamina)
		{
			CurrentStamina += StaminaRecoveryPerSecond * DeltaSeconds;
			if (CurrentStamina >= MaxStamina)
			{
				CurrentStamina = MaxStamina;
				FillUpStamina(WIDCharacter);
			}
		}
	}
}

void AWIDPlayerState::RunOutStamina(AWIDCharacter* WIDCharacter)
{
	if (WIDCharacter == nullptr)
		return;

	WIDCharacter->Walk();
}

void AWIDPlayerState::FillUpStamina(AWIDCharacter* WIDCharacter) EmptyFunction
