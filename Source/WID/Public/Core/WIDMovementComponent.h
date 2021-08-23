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
	/** State can only be changed on the corresponding state */
	UPROPERTY(EditDefaultsOnly)
		EWIDMovementState AllowTargetState = EWIDMovementState::None;
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
	virtual void SetPostLandedPhysics(const FHitResult& Hit) override;
	virtual float GetMaxSpeed() const override;
	// }} UMovementComponent Interface

public:
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
	/** Restore old movement state and the mobility changes depneding on the corresponding movement state */
	virtual void RestoreMovmenetState();
	/**
	* Save the new movement state and apply it as a movement state later as RestoreMovementState.
	* @param PendingTime - Call the RestoreMovementState after a PendingTime. If value is 0, you must explicitly invoke the RestoreMovementState.
	*/
	virtual void PendingMovementState(const EWIDMovementState NewMovmenetState, const float PendingTime = 0.0f);

protected:
	/** Save old movement state to bring it back later */
	virtual void SaveMovementState(const EWIDMovementState OldMovmenetState);

	/** Returns true if the character can save this movemenet state */
	virtual bool CanSaveMovemenetState(const EWIDMovementState MovmenetState) const;
	/** Returns true if the character can restore last movemenet state */
	virtual bool CanRestoreMovementState(const EWIDMovementState CurrentMovmenetState, const EWIDMovementState LastMovmenetState) const;

public:
#if WITH_EDITORONLY_DATA
	/** Apply the desired speed when greadter than zero, for debugging */
	UPROPERTY(Transient, EditInstanceOnly, BlueprintReadOnly, Category = "State")
		float CheatSpeed;
#endif // WITH_EDITORONLY_DATA

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
