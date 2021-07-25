// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WIDAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WID_API UWIDAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// {{ UAnimInstance Interface
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	// }} UAnimInstance Interface

public:
	void PlayDeathAnimation();

protected:
	/** Curve for jump animation rate to determin distance from ground */
	UPROPERTY(EditDefaultsOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		class UCurveFloat* JumpAnimRateCurve;

	/** Jump animation start point for natural animation. If the character can ready to jump, set to default value */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		float JumpAnimStartPosition = 0.0f;

protected:
	/** Is the character floating in the air? */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
		bool bIsInAir;

	/** Is the character walking slowly? */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
		bool bIsSlowWalking;

	/** Is the character jumping? */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
		bool bIsJumping;

	/** The current speed at which the character moves */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
		float CurrentSpeed;

	/** The current speed at which the character moves based on the X and Y axes */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
		float CurrentSpeed2D;

	/** how far the character looks to the direction */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
		float CurrentLookDegree;

	/** Rate of jump animation. The character's jump animation rate varies depneing on the distance from ground */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		float JumpAnimRate = 1.0f;

	/** How fast you'll play the animation you're looking at */
	UPROPERTY(Transient, EditDefaultsOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		float LookAnimRate = 1.0f;

	/** On death, another state machine will be activated */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		bool bDied = false;

	/** Index of death animation to play is specified randomly when died */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		int32 DeathAnimationIndex;

private:
	/** Default value of JumpAnimStartPosition */
	float DefaultJumpAnimStartPosition;

};
