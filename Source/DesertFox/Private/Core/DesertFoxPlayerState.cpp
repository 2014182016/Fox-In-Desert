// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DesertFoxPlayerState.h"
#include "Core/DesertFoxCharacter.h"
#include "Core/DesertFoxMovementComponent.h"

ADesertFoxPlayerState::ADesertFoxPlayerState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADesertFoxPlayerState::BeginPlay()
{
	Super::BeginPlay();

	CurrentStamina = MaxStamina;
	CurrentHealth = MaxHealth;
}

void ADesertFoxPlayerState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateStamina(DeltaSeconds);
}

void ADesertFoxPlayerState::UpdateStamina(float DeltaSeconds)
{
	ADesertFoxCharacter* DesertFoxCharacter = GetPawn<ADesertFoxCharacter>();
	if (DesertFoxCharacter == nullptr)
		return;

	UDesertFoxMovementComponent* DesertFoxMovement = Cast<UDesertFoxMovementComponent>(DesertFoxCharacter->GetMovementComponent());
	if (DesertFoxMovement == nullptr)
		return;

	if (DesertFoxMovement->IsRunning())
	{
		if (CurrentStamina > 0.0f)
		{
			CurrentStamina -= StaminaConsumptionPerSecond * DeltaSeconds;
			if (CurrentStamina <= 0.0f)
			{
				CurrentStamina = 0.0f;
				RunOutStamina(DesertFoxCharacter);
			}
		}
	}
	else
	{
		if (CurrentStamina < MaxStamina)
		{
			CurrentStamina += StaminaRecoveryPerSecond * DeltaSeconds;
			if (CurrentStamina >= MaxStamina)
			{
				CurrentStamina = MaxStamina;
				FillUpStamina(DesertFoxCharacter);
			}
		}
	}
}

void ADesertFoxPlayerState::RunOutStamina(ADesertFoxCharacter* DesertFoxCharacter)
{
	if (DesertFoxCharacter == nullptr)
		return;

	DesertFoxCharacter->Walk();
}

void ADesertFoxPlayerState::FillUpStamina(ADesertFoxCharacter* DesertFoxCharacter) EmptyFunction