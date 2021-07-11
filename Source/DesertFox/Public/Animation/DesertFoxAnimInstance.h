// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DesertFoxAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DESERTFOX_API UDesertFoxAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// {{ UAnimInstance Interface
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	// }} UAnimInstance Interface

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		bool bIsInAir;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		bool bIsSlowWalking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		bool bIsJumping;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		float CurrentSpeed;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		float CurrentSpeed2D;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		float JumpAnimRate = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		class UCurveFloat* JumpAnimRateCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		float JumpAnimStartPosition = 0.0f;

private:
	float DefaultJumpAnimStartPosition;

};
