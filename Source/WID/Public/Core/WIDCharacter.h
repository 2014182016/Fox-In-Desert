// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WIDTypes.h"
#include "OptionalWrapper.h"
#include "GameFramework/Character.h"
#include "WIDCharacter.generated.h"

UCLASS()
class AWIDCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWIDCharacter(const FObjectInitializer& ObjectInitializer);

	// {{ AActor Interface
	virtual void Destroyed() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	// }} AActor Interface

	// {{ APawn Interface
	virtual void AddMovementInput(FVector WorldDirection, float ScaleValue = 1.0f, bool bForce = false) override;
	// }} APawn Interface
	
	// {{ ACharacter Interface
	virtual void Landed(const FHitResult& Hit) override;
	// }} ACharacter Interface

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** Characater turns into a running movement state */
	virtual void Run();
	/** Characater turns into a walking movement state */
	virtual void Walk();
	/** Characater turns into a slow walking movement state */
	virtual void SlowWalk();
	/** Characater turns into a previous movement state  */
	virtual void RestoreMovementState();

	/** Characater begins to prepare for the jump  */
	virtual void StartJump();
	/** Characater performs jump */
	virtual void RealJump();
	/** Returns true if the character can ready to jump */
	virtual bool CanReadyToJump() const;

	// {{ Binding Action Function for Timeline
	void StartLookLeft();
	void StopLookLeft();

	void StartLookRight();
	void StopLookRight();
	// }} Binding Action Function for Timeline

	/** Call by player state when character died */
	void NotifyDied();

	FORCEINLINE bool IsDied() const { return bDied; }

	/** Character goes to sleep and switches to a state where movement is impossible */
	virtual void Sleep();
	/** Character wakes up and switches to a state where movement is possible */
	virtual void WakeUp();

	/** Delay enable Jump to avoid appearance of  unnatural jumping animations in consecutive junmps by blending animation */
	virtual void EnableJump();

protected:
	// {{ AActor Interface
	virtual void BeginPlay() override;
	// }} AActor Interface

protected:
	/** Tilt according to the normal directiuon of the floor */
	virtual void CheckTiltBody(float DeltaTime);

	/** Find where the foot belong */
	virtual void CheckFootPlacement(float DeltaTime);

private:
	/** Check and return only acceptable normal */
	FVector CheckAcceptableNormal(const FVector& InNormal) const;

protected:
	// {{ Timeline Binding Function
	UFUNCTION()
		void LeftLookHandleProgress(float InterpValue);

	UFUNCTION()
		void RightLookHandleProgress(float InterpValue);
	// }} Timeline Binding Function

public:
	/** Tilt according to the normal direction of the floor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		uint8 bTiltBody : 1;

	/** Whether to enable foot ik */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
		uint8 bUseFootIK : 1;

public:
	/** Curve that indicates how far the character looks to the left whene pressed left */
	float CurrentLookDegree;

	/** The last time moved */
	float LastMoveStamp;

	/** IK location for foot position */
	FVector FootIKLocations[LEG_NUM];

	/** IK location for hip position */
	FVector HipIKOffset;

protected:
	/** Binding the camera to the character for fixed distance */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Third person camera for player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	/** Apply collision to the front of the body to prevent the mesh from penetrating */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* FrontBodyCollision;

protected:
	/** If the value is set, the jump is executed after a certain period of time. If not, it's done immediately */
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		FOptionalFloat ReadyToJumpTime = 0.2f;

	/** Jump is possible after a certain period of time after landing */
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float DelayActivateJump = 0.1f;

	/** Timeline play rate in context. X is forward play rate, Y is reverse play rate */
	UPROPERTY(EditAnywhere, Category = "Timeline", meta = (AllowPrivateAccess = "true"))
		FVector2D LookPlayRate = FVector2D(1.0f);

	/** Timeline play rate in context when opposition input pressed. X is forward play rate, Y is reverse play rate */
	UPROPERTY(EditAnywhere, Category = "Timeline", meta = (AllowPrivateAccess = "true"))
		FVector2D OppositionLookPlayRate = FVector2D(1.0f);

	/** Adjust the speed at which the character rotates according to floor normal */
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float StandingRotationInterpSpeed = 4.0f;

	/** The angle with the floor normal must be greater than this value to apply character rotation */
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float CharacterRotationMaxDegree = 30.0f;

	/** Speed to interpolate to the point of position using IK */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
		float IKPositionIterpSpeed = 10.0f;

protected:
	/** True on death */
	bool bDied;

private:
	/** Curve that indicates how far the character looks to the left whene pressed left */
	UPROPERTY(EditDefaultsOnly, Category = "Timeline", meta = (AllowPrivateAccess = true))
		class UCurveFloat* LeftLookCurve;

	/** Curve that indicates how far the character looks to the left whene pressed right */
	UPROPERTY(EditDefaultsOnly, Category = "Timeline", meta = (AllowPrivateAccess = true))
		class UCurveFloat* RightLookCurve;

private:
	// {{ Timeline Components
	UPROPERTY()
		class UTimelineComponent* LeftLookTimelineComponent;

	UPROPERTY()
		class UTimelineComponent* RightLookTimelineComponent;
	// }} Timeline Components

private:
	/** It indicates how far the rotation animation should go. X is left value, Y is right value */
	FVector2D LookAmount;
	/** Is the character possible to jump */
	bool bCanJump;

};

