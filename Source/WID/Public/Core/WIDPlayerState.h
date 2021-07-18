// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WIDTypes.h"
#include "GameFramework/PlayerState.h"
#include "WIDPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class WID_API AWIDPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AWIDPlayerState();

	// {{ AActor Interface
	virtual void Tick(float DeltaSeconds) override;
	// }} AActor Interface

	FORCEINLINE float GetCurrentStamina() const { return CurrentStamina; }
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

protected:
	// {{ AActor Interface
	virtual void BeginPlay() override;
	// }} AActor Interface

protected:
	/** Renew the stamina every tick */
	virtual void UpdateStamina(float DeltaSeconds);
	/** Call this function when run out of stamina */
	virtual void RunOutStamina(class AWIDCharacter* WIDCharacter);
	/** Call this function when the stamina is full */
	virtual void FillUpStamina(class AWIDCharacter* WIDCharacter);

protected:
	/** The amount of stamina that can be charged as much as possible */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = true, ClampMin = 0.0, UIMin = 0.0))
		float MaxStamina = 100.0f;

	/** The amount of health that can be charged as much as possible */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = true, ClampMin = 0.0, UIMin = 0.0))
		float MaxHealth = 100.0f;

	/** The amount of stamina consumed per second */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = true, ClampMin = 0.0, UIMin = 0.0))
		float StaminaConsumptionPerSecond = 5.0f;

	/** The amount of stamina recovered per second */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = true, ClampMin = 0.0, UIMin = 0.0))
		float StaminaRecoveryPerSecond = 5.0f;

protected:
	/** The current amount of stamina by calculation */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true, ClampMin = 0.0))
		float CurrentStamina;
	/** The current amount of health by calculation */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true, ClampMin = 0.0))
		float CurrentHealth;
	
};
