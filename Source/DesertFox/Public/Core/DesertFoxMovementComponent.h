// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DesertFoxTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DesertFoxMovementComponent.generated.h"

USTRUCT(BlueprintType)
struct FMovemenetStateInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bOrientRotationToMovement = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator RotationRate = FRotator(0.0f, 270.0f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float JumpZVelocity = 600.0f;
};

/**
 * 
 */
UCLASS()
class DESERTFOX_API UDesertFoxMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	// {{ UMovementComponent Interface
	virtual float GetMaxSpeed() const override;
	// }} UMovementComponent Interface

	UFUNCTION(BlueprintPure)
		bool IsRunning() const { return CurrentMovementState == EDesertFoxMovementState::Running; }

	UFUNCTION(BlueprintPure)
		bool IsSlowWalking() const { return CurrentMovementState == EDesertFoxMovementState::SlowWalking; }

	UFUNCTION(BlueprintPure)
		bool IsJumping() const { return CurrentMovementState == EDesertFoxMovementState::Jumping; }

	virtual void SetMovementState(const EDesertFoxMovementState NewMovmenetState);
	virtual void SaveMovementState(const EDesertFoxMovementState OldMovmenetState);
	virtual void RestoreMovmenetState();

public:
	float DistanceToFloorWhileFalling;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		EDesertFoxMovementState CurrentMovementState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float MaxRunSpeed = 780.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float MaxSlowWalkSpeed = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		TMap<EDesertFoxMovementState, FMovemenetStateInfo> MovementStateInfoMap;

private:
	EDesertFoxMovementState LastMovementState;
	float LastMaxSpeed;

};
