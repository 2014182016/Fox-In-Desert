// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WIDTypes.h"
#include "OptionalWrapper.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WIDMovementComponent.generated.h"

/** Information to change the value of the character accoring to the character movement state */
USTRUCT(BlueprintType)
struct FMovemenetStateInfo
{
	GENERATED_USTRUCT_BODY()

public:
	/** Change the character's value through character movement */
	void Set(class UWIDMovementComponent* OtherMovement) const;

public:
	/** If it is set, override to bOrientRotationToMovement in character movement */
	UPROPERTY(EditDefaultsOnly)
		FOptionalBool bOrientRotationToMovement = true;
	/** If it is set, override to RotationRate in character movement */
	UPROPERTY(EditDefaultsOnly)
		FOptionalRotator RotationRate = FRotator(0.0f, 270.0f, 0.0f);
	/** If it is set, override to JumpZVelocity in character movement */
	UPROPERTY(EditDefaultsOnly)
		FOptionalFloat JumpZVelocity = 360.0f;
	/** If it is set, override to speed in character movement */
	UPROPERTY(EditDefaultsOnly)
		FOptionalFloat Speed = 600.0f;
};

/**
 * 
 */
UCLASS()
class WID_API UWIDMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	// {{ UActorComponent Interface
	virtual void BeginPlay() override;
	// }} UActorComponent Interface

	// {{ UMovementComponent Interface
	virtual void PhysFalling(float deltaTime, int32 Iterations) override;
	// }} UMovementComponent Interface

	/** Returns true if the character is in the running movement state */
	virtual bool IsRunning() const { return CurrentMovementState == EWIDMovementState::Running; }
	/** Returns true if the character is in the slow walking movement state */
	virtual bool IsSlowWalking() const { return CurrentMovementState == EWIDMovementState::SlowWalking; }
	/** Returns true if the character is in the jumping movement state */
	virtual bool IsJumping() const { return CurrentMovementState == EWIDMovementState::Jumping; }

	/** Returns current character movement state, decided from inputs */
	EWIDMovementState GetCurrentMovementState() const { return CurrentMovementState; }

	/** Returns true if the character can change to the running movement state */
	virtual bool CanRun() const;
	/** Returns true if the character can change to the walking movement state */
	virtual bool CanWalk() const;
	/** Returns true if the character can change to the slow walking movement state */
	virtual bool CanSlowWalk() const;
	/** Returns true if the character can change to the jumping movement state */
	virtual bool CanJump() const;

	/** 
	* Change new movement state and the mobility changes depneding on the corresponding movement state.
	* @param bSaveMovement - If true, save current movement state to restore later
	*/
	virtual void SetMovementState(const EWIDMovementState NewMovmenetState, bool bSaveMovement = true);
	/** Save old movement state to bring it back later */
	virtual void SaveMovementState(const EWIDMovementState OldMovmenetState);
	/** Restore old movement state and the mobility changes depneding on the corresponding movement state */
	virtual void RestoreMovmenetState();

public:
	/** Distance from ground when jumping */
	float DistanceToFloorWhileFalling;

protected:
	/** Current movement State applied to character movement */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		EWIDMovementState CurrentMovementState;

	/** Movement information container in accordance with movement state */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		TMap<EWIDMovementState, FMovemenetStateInfo> MovementStateInfoMap;

private:
	/** Movement state to restore later */
	EWIDMovementState LastMovementState;

};
