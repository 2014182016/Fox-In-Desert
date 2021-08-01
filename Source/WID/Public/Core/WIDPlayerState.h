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

public:
	FORCEINLINE float GetCurrentStamina() const { return CurrentStamina; }
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	/** Return the current state calculated as a value between 0 and 1 */
	float GetStaminaPercent() const;
	float GetHealthPercent() const;

	/** Reflects the value by adding it to the current state */
	void AddStamina(const float Value);
	void AddHealth(const float Value);
	
public:
	/** Invoke bound functions when health reches 0 */
	DECLARE_MULTICAST_DELEGATE(FDiedDelegate);
	FDiedDelegate DiedDelegate;

;protected:
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

public:
#if WITH_EDITOR
	/** Stamina not reduced, for debugging */
	UPROPERTY(Transient, EditInstanceOnly, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true))
		bool bInfiniteStamina;
#endif // WITH_EDITOR

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
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true))
		float CurrentStamina;

	/** The current amount of health by calculation */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true))
		float CurrentHealth;
	
};
