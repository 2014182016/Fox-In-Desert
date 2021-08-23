// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WIDPlayerState.h"
#include "Core/WIDCharacter.h"
#include "Core/WIDMovementComponent.h"
#include "Core/WIDPlayerController.h"
#include "Core/WIDHUD.h"

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

	if (!bIsExhausted)
	{
		if (WIDMovement->IsRunning())
		{
			if (CurrentStamina > 0.0f)
			{
				AddStamina(-StaminaConsumptionPerSecond * DeltaSeconds);
			}
		}
	}
	
	if (!WIDMovement->IsJumping() && !WIDMovement->IsRunning())
	{
		if (CurrentStamina < MaxStamina)
		{
			AddStamina(StaminaRecoveryPerSecond * DeltaSeconds);
		}
	}
}

void AWIDPlayerState::RunOutStamina()
{
	AWIDCharacter* WIDCharacter = GetPawn<AWIDCharacter>();
	if (WIDCharacter == nullptr)
		return;

	UWIDMovementComponent* WIDMovement = Cast<UWIDMovementComponent>(WIDCharacter->GetMovementComponent());
	if (WIDMovement == nullptr)
		return;

	if (WIDMovement->IsJumping())
	{
		WIDMovement->PendingMovementState(EWIDMovementState::Idle);
	}
	else
	{
		WIDCharacter->Walk();
	}

	bIsExhausted = true;

	AWIDPlayerController* WIDPlayerController = Cast<AWIDPlayerController>(GetOwner());
	if (IsValid(WIDPlayerController))
	{
		AWIDHUD* WIDHUD = WIDPlayerController->GetHUD<AWIDHUD>();
		if (IsValid(WIDHUD))
		{
			WIDHUD->UpdateHudEventWithValue(EHudType::PlayerState, EHudEvent::UpdateStaminaState, static_cast<int32>(EStaminaState::Exhaustion));
		}
	}
}

void AWIDPlayerState::FillUpStamina() EmptyFunction

float AWIDPlayerState::GetStaminaPercent() const
{
	return (MaxStamina < FLT_EPSILON) ? 0.0f : FMath::Clamp<float>(CurrentStamina / MaxStamina, 0.0f, 1.0f);
}

float AWIDPlayerState::GetHealthPercent() const
{
	return (MaxHealth < FLT_EPSILON) ? 0.0f : FMath::Clamp<float>(CurrentHealth / MaxHealth, 0.0f, 1.0f);
}

void AWIDPlayerState::AddStamina(const float Value)
{
#if	UE_BUILD_SHIPPING
	CurrentStamina = FMath::Clamp<float>(CurrentStamina + Value, 0.0f, MaxStamina);
#else // UE_BUILD_SHIPPING
	CurrentStamina = bInfiniteStamina ? 100.0f : FMath::Clamp<float>(CurrentStamina + Value, 0.0f, MaxStamina);
#endif // UE_BUILD_SHIPPING

	if (CurrentStamina <= 0.0f)
	{
		CurrentStamina = 0.0f;
		RunOutStamina();
	}
	else if (CurrentStamina >= MaxStamina)
	{
		CurrentStamina = MaxStamina;
		FillUpStamina();
	}
	
	if (bIsExhausted)
	{
		if (CurrentStamina >= StaminaRecoverFromExhaustion)
		{
			RecoverFromExhaustion();
		}
	}
}

void AWIDPlayerState::AddHealth(const float Value)
{
	CurrentHealth = FMath::Clamp<float>(CurrentHealth + Value, 0.0f, MaxHealth);

	AWIDPlayerController* WIDPlayerController = Cast<AWIDPlayerController>(GetOwner());
	if (IsValid(WIDPlayerController))
	{
		AWIDHUD* WIDHUD = WIDPlayerController->GetHUD<AWIDHUD>();
		if(IsValid(WIDHUD))
		{
			WIDHUD->UpdateHudEventWithValue(EHudType::PlayerState, EHudEvent::UpdateHealth, CurrentHealth);
		}
	}

	if (CurrentHealth <= 0.0f)
	{
		if (DiedDelegate.IsBound())
		{
			DiedDelegate.Broadcast();
		}
	}
}

void AWIDPlayerState::ConsumeJumpingStamina()
{
	AddStamina(-JumpingStaminaConsumption);
}

void AWIDPlayerState::RecoverFromExhaustion()
{
	bIsExhausted = false;

	AWIDPlayerController* WIDPlayerController = Cast<AWIDPlayerController>(GetOwner());
	if (IsValid(WIDPlayerController))
	{
		AWIDHUD* WIDHUD = WIDPlayerController->GetHUD<AWIDHUD>();
		if (IsValid(WIDHUD))
		{
			WIDHUD->UpdateHudEventWithValue(EHudType::PlayerState, EHudEvent::UpdateStaminaState, static_cast<int32>(EStaminaState::Normal));
		}
	}
}
